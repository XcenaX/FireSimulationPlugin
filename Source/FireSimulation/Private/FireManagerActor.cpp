#include "FireManagerActor.h"
#include "FireGridManager.h"
#include "SmokeManager.h"
#include "FireSimulationComponent.h"
#include <MaterialData.h>
#include <Async/Async.h>
#include <MaterialDataManager.h>
#include "Misc/DateTime.h"
#include "HAL/PlatformTime.h"

// Sets default values
AFireManagerActor::AFireManagerActor()
{
    // Set this actor to call Tick() every frame. You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AFireManagerActor::BeginPlay()
{
	Super::BeginPlay();

	TotalSimulationTime = 0;

	SmokeManager = NewObject<USmokeManager>(this);
	SmokeManager->AddToRoot();
	if (SmokeManager)
		SmokeManager->Initialize(GetWorld());

	if (!SmokeManager->CorrectlySetuped()) {
		SmokeManager->ConditionalBeginDestroy();
		SmokeManager = nullptr;
	}


    FString AssetPath;
    UObject* Asset = nullptr;
    if (GConfig->GetString(
        TEXT("FireSimulationSettings"),
        TEXT("FireParticle"),
        AssetPath,
        GEditorPerProjectIni
    ))
    {
        Asset = LoadObject<UParticleSystem>(nullptr, *AssetPath);        
    }
    

    FString LoadedCellSize = "";
    GConfig->GetString(
        TEXT("FireSimulationSettings"),
        TEXT("CubesAmount"),
        LoadedCellSize,
        GEditorPerProjectIni
    );

    FString LoadedThreads = "";
    GConfig->GetString(
        TEXT("FireSimulationSettings"),
        TEXT("Threads"),
        LoadedThreads,
        GEditorPerProjectIni
    );

    FString LoadedFireSize = "";
    GConfig->GetString(
        TEXT("FireSimulationSettings"),
        TEXT("FireSize"),
        LoadedFireSize,
        GEditorPerProjectIni
    );

	FString LoadedUnitsPerMeter = "";	
	GConfig->GetString(
        TEXT("FireSimulationSettings"),
        TEXT("UnitsPerMeter"),
        LoadedUnitsPerMeter,
        GEditorPerProjectIni
    );

    int32 CellSize = FCString::Atoi(*LoadedCellSize);
	Threads = FCString::Atoi(*LoadedThreads);
    int32 FireSize = FCString::Atoi(*LoadedFireSize);
    UnitsPerMeter = FCString::Atoi(*LoadedUnitsPerMeter);

    GridManager = NewObject<UFireGridManager>(this, FName(TEXT("GridManager")));
	GridManager->AddToRoot();
    InitializeGrid(CellSize, Threads, FireSize, Asset);
	InitializeFireSpread();

	FEditorDelegates::EndPIE.AddUObject(this, &AFireManagerActor::OnEndPIE);
}

float AFireManagerActor::GetSpreadFactor(float LinearSpeed) const{
	float SpreadSpeedInUnrealUnits = LinearSpeed *  UnitsPerMeter;
	float SpreadFactor = SpreadSpeedInUnrealUnits / 100.0f;
	return FMath::Clamp(SpreadFactor, 1.0f, 10.0f);
};


void AFireManagerActor::StartFireThread(int32 CellSize, int32 NewThreads, int32 FireDistance, UObject* FireParticle) {

	Threads = GridManager->Threads;
	TotalSimulationTime = 0;

    InitializeGrid(CellSize, NewThreads, FireDistance, FireParticle);

	Async(EAsyncExecution::Thread, [this]() {
		while (!Stop) {
			double Start = FPlatformTime::Seconds();

			UpdateFireSpread();

			double End = FPlatformTime::Seconds();
			double ElapsedSeconds = End - Start;

			double TimeToSleep = 1.0f - ElapsedSeconds;
			if (TimeToSleep > 0) {
				FPlatformProcess::Sleep(TimeToSleep);
			}
			TotalSimulationTime++;
		}
		});

	FEditorDelegates::EndPIE.AddUObject(this, &AFireManagerActor::OnEndPIE);
}

// After the game ends in the editor, return all burned actors to their places and extinguish the fire
void AFireManagerActor::OnEndPIE(const bool bIsSimulating)
{
    UE_LOG(LogTemp, Warning, TEXT("GAME ENDED"));
    
    RestoreScene();

    CheckList.Empty();
    NewList.Empty();
    FireList.Empty();

    if (GridManager) {
        GridManager->ClearGrid();
    }

    if (SmokeManager && SmokeManager->graph) {
        SmokeManager->graph->ClearGraph();
        SmokeManager->Cleanup();
        SmokeManager->graph = nullptr;
        SmokeManager = nullptr;
    }
}

// Called every frame
void AFireManagerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TimeAccumulator += DeltaTime;

    if (TimeAccumulator >= 1.0f)
    {        
        if (JobDone)
        {
			if (SmokeManager && SmokeManager->CorrectlySetuped()) {
				SmokeManager->UpdateSmoke();
				SmokeManager->TotalTime++;
			}
            Async(EAsyncExecution::Thread, [this]()
            {
                UpdateFireSpread();
            });
        }
        
        TimeAccumulator = 0.0f;
    }    
}

void AFireManagerActor::InitializeFireSpread()
{    
	// Move initially burning actors to the list for further processing
    TArray<FGridCell*> BurningCells = GridManager->GetBurningCells();
    UE_LOG(LogTemp, Warning, TEXT("BURNING LIST: %d"), BurningCells.Num());

    NewList.Empty(BurningCells.Num());
    for (int i = 0; i < BurningCells.Num(); i++) {
        NewList.Add(BurningCells[i]);
    }
}

void AFireManagerActor::UpdateFireSpread()
{
    JobDone = false;
    if (CheckList.Num() > 0 || NewList.Num() > 0 || FireList.Num() > 0) {
        double TotalTime = 0;
        double Start = FPlatformTime::Seconds();

		if (CheckList.Num() > 500) {
			parallelProcessList(CheckList, [this](int32 Start, int32 End, TArray<FVector>& CoordsToRemove) {
				this->processCheckList(Start, End, CoordsToRemove);
				}, CheckListRemovalIndices);

		}
		else {
			processCheckList(0, CheckList.Num(), CheckListRemovalIndices);
		}
		RemoveCellsByCoords(CheckList, CheckListRemovalIndices);

		UE_LOG(LogTemp, Warning, TEXT("CheckList: %d; FireList: %d; NewList: %d"), CheckList.Num(), FireList.Num(), NewList.Num());
		double End = FPlatformTime::Seconds();
		double ElapsedSeconds = End - Start;
		TotalTime += ElapsedSeconds;

		Start = FPlatformTime::Seconds();

		if (NewList.Num() > 500) {
			parallelProcessList(NewList, [this](int32 Start, int32 End, TArray<FVector>& CoordsToRemove) {
				this->processNewList(Start, End, CoordsToRemove);
				}, NewListRemovalIndices);

		}
		else {
			processNewList(0, NewList.Num(), NewListRemovalIndices);
		}
		RemoveCellsByCoords(NewList, NewListRemovalIndices);

		End = FPlatformTime::Seconds();
		ElapsedSeconds = End - Start;
		TotalTime += ElapsedSeconds;

		Start = FPlatformTime::Seconds();


        End = FPlatformTime::Seconds();
        ElapsedSeconds = End - Start;
        TotalTime += ElapsedSeconds;

		TotalSimulationTime++;
		UE_LOG(LogTemp, Warning, TEXT("Total Time: %f сек"), TotalTime);
		UE_LOG(LogTemp, Warning, TEXT("Total SIMULATION Time: %d сек"), TotalSimulationTime);
    }
    JobDone = true;
}

void AFireManagerActor::InitializeGrid(int32 CellSize, int32 NewThreads, int32 FireDistance, UObject* FireParticle)
{
    Threads = NewThreads;
    
    UWorld* World = GetWorld();
    AGridActor* GridActor = nullptr;
    for (TActorIterator<AGridActor> It(World); It; ++It)
    {
        GridActor = *It;
        break;
    }
    
    GridManager->InitializeGrid(World, GridActor, CellSize, Threads, FireDistance, FireParticle);
    GridManager->PopulateGridWithActors();
    InitializeFireSpread();
}

bool AFireManagerActor::Contains(TArray<FGridCell*> List, FGridCell* Cell) {
	for (FGridCell* Item : List) {
		if (Item == Cell) {
			return true;
		}
	}
	return false;
}

bool AFireManagerActor::Contains(TArray<FGridCell*> List, FGridCell Cell) {
	for (FGridCell* Item : List) {
		if (Item->x == Cell.x && Item->y == Cell.y && Item->z == Cell.z) {
			return true;
		}
	}
	return false;
}

void AFireManagerActor::StopFireThread()
{
	Stop = true;
}

void AFireManagerActor::processCheckList(int32 StartIndex, int32 EndIndex, TArray<FVector>& CoordsToRemove) {
	FScopeLock ScopeLock(&ListMutex);
	for (int32 i = StartIndex; i < EndIndex; ++i)
	{
		FGridCell* Cell = CheckList[i];

		if (!Cell) continue;

		if (Cell->OccupyingActor == nullptr || Cell->Status > EMPTY) {
			CoordsToRemove.Add(FVector(Cell->x, Cell->y, Cell->z));
			continue;
		}
		
		int32 FP = CalculateFP(Cell);
		float LinearSpeed = 0.8f; // Default value

		UFireSimulationComponent* FireComp = GridManager->ActorToFireCompMap.FindRef(Cell->OccupyingActor);
		if (FireComp)
		{
			const FMaterialData* Material = FMaterialDataManager::Get().GetMaterialData(*(FireComp->SelectedMaterial));
			if (!Material) continue;
			LinearSpeed = Material->LinearFlameSpeed;
		}

		float SpreadFactor = GetSpreadFactor(LinearSpeed);

		// 26 - Empirically determined maximum flame speed
		float Probability = ((LinearSpeed * FP) / 26) * SpreadFactor;

		if (i == StartIndex + 1) {
			UE_LOG(LogTemp, Warning, TEXT("FP: %d; Probability: %f"), FP, Probability);
		}

		if (FMath::RandRange(0.0f, 1.0f) < Probability)
		{
			NewList.Add(Cell);
			CoordsToRemove.Add(FVector(Cell->x, Cell->y, Cell->z));
		}
	}
}

void AFireManagerActor::processNewList(int32 StartIndex, int32 EndIndex, TArray<FVector>& CoordsToRemove) {
	FScopeLock ScopeLock(&ListMutex);
	for (int32 i = StartIndex; i < EndIndex; ++i) {
		FGridCell* cell = NewList[i];

		if (cell->OccupyingActor == nullptr) {
			CoordsToRemove.Add(FVector(cell->x, cell->y, cell->z));
			continue;
		}

		UFireSimulationComponent* FireComp = GridManager->ActorToFireCompMap.FindRef(cell->OccupyingActor);

		FireList.Add(cell);
		cell->Status = BURNING;
		
		CoordsToRemove.Add(FVector(cell->x, cell->y, cell->z));
		if (cell->FireActor == nullptr) {
			AsyncTask(ENamedThreads::GameThread, [this, cell]() {
				GridManager->CreateFireActor(cell);
				});
		}
		
		// If the room of this actor has not yet caught fire, then perform a merge
		if (SmokeManager && SmokeManager->CorrectlySetuped()) {
			if (FireComp && !SmokeManager->GetRoomStatusForActor(cell->OccupyingActor->GetName()) && !FireComp->IsWall) {
				int32 RoomID = SmokeManager->GetRoomIdForActor(cell->OccupyingActor->GetName());
				if (RoomID >= 0) {
					UE_LOG(LogTemp, Warning, TEXT("MERGE ROOM : %d ; Actor: %s"), RoomID, *cell->OccupyingActor->GetName());
					SmokeManager->SetRoomStatus(RoomID, true);
					SmokeManager->graph->MergeToSourceRoom(RoomID);
				}
			}
		}

		int32 x = cell->x;
		int32 y = cell->y;
		int32 z = cell->z;

		for (int32 dx = -1; dx <= 1; dx++) {
			for (int32 dy = -1; dy <= 1; dy++) {
				for (int32 dz = -1; dz <= 1; dz++) {
					if (dx == 0 && dy == 0 && dz == 0) continue;

					int32 newX = x + dx;
					int32 newY = y + dy;
					int32 newZ = z + dz;

					// Check that the coordinates are within the grid limits
					if (newX >= 0 && newX < GridManager->ElementsAmountX &&
						newY >= 0 && newY < GridManager->ElementsAmountY &&
						newZ >= 0 && newZ < GridManager->ElementsAmountZ) {

						FGridCell& Cell = GridManager->GetCell(newX, newY, newZ);

						if (Cell.Status == EMPTY && Cell.OccupyingActor && !Contains(CheckList, Cell)) {
							CheckList.Add(&Cell);
						}
					}
				}
			}
		}
	}
}

void AFireManagerActor::processFireList(int32 StartIndex, int32 EndIndex, TArray<FVector>& CoordsToRemove) {
	FScopeLock ScopeLock(&ListMutex);
	for (int32 i = StartIndex; i < EndIndex; ++i) {
		FGridCell* cell = FireList[i];

		if (cell->OccupyingActor == nullptr) {
			continue;
		}

		UFireSimulationComponent* FireComp = GridManager->ActorToFireCompMap.FindRef(cell->OccupyingActor);

		if (FireComp->IsWall) {
			continue;
		}

		if (cell->Status == BURNING) {
			cell->time += 1;
			const FMaterialData* SelectedMaterial = FMaterialDataManager::Get().GetMaterialData(*FireComp->SelectedMaterial);

			float A = 1.05 * SelectedMaterial->BurningRate * pow(SelectedMaterial->LinearFlameSpeed, 2);
			float burntMass = A * pow(cell->time, 3);

			if (cell->mass <= burntMass && cell->time > 2) {
				cell->Status = BURNT;
				GridManager->ActorCellsCount[cell->OccupyingActor]--;

				BurntList.Add(cell);
				CoordsToRemove.Add(FVector(cell->x, cell->y, cell->z));
			}
		}
	}
}

void AFireManagerActor::parallelProcessList(TArray<FGridCell*>& List, TFunction<void(int32, int32, TArray<FVector>&)> ProcessFunction, TArray<FVector>& GlobalCoordsToRemove) {
	int32 TotalSize = List.Num();
	int32 MaxElementsPerTask = FMath::CeilToInt((float)TotalSize / (float)Threads);

	// List for storing Future results of each asynchronous task
	TArray<TFuture<void>> Futures;

	for (int32 Index = 0; Index < Threads; ++Index) {
		int32 StartIndex = Index * MaxElementsPerTask;
		int32 EndIndex = FMath::Min(StartIndex + MaxElementsPerTask, TotalSize);

		Futures.Add(Async(EAsyncExecution::ThreadPool, [this, StartIndex, EndIndex, &List, &ProcessFunction, &GlobalCoordsToRemove]() {
			TArray<FVector> LocalCoordsToRemove;
			ProcessFunction(StartIndex, EndIndex, LocalCoordsToRemove);

			// Lock the mutex for safe access to the global list
			FScopeLock ScopeLock(&ListMutex);
			for (const FVector& Coord : LocalCoordsToRemove) {
				GlobalCoordsToRemove.Add(Coord);
			}
			}));
	}

	// Wait for all tasks to complete
	for (TFuture<void>& Future : Futures) {
		Future.Wait();
	}
}

void AFireManagerActor::RemoveCellsByCoords(TArray<FGridCell*>& List, TArray<FVector>& CoordsToRemove)
{
	FScopeLock ScopeLock(&ListMutex);

	for (int32 Index = List.Num() - 1; Index >= 0; --Index)
	{
		const FGridCell* Cell = List[Index];
		const FVector CellCoords(Cell->x, Cell->y, Cell->z);

		for (const FVector& CoordToRemove : CoordsToRemove)
		{
			if (CellCoords.X == CoordToRemove.X && CellCoords.Y == CoordToRemove.Y && CellCoords.Z == CoordToRemove.Z)
			{
				List.RemoveAt(Index);
				break;
			}
		}
	}
	CoordsToRemove.Empty();
}

int AFireManagerActor::CalculateFP(FGridCell* Cell) {
	int directNeighborCount = 0;
	int diagonalNeighborCount = 0;
	int bottomNeighborCount = 0;

	for (int32 dx = -1; dx <= 1; dx++) {
		for (int32 dy = -1; dy <= 1; dy++) {
			for (int32 dz = -1; dz <= 1; dz++) {
				if (dx == 0 && dy == 0 && dz == 0) continue;

				int32 newX = Cell->x + dx;
				int32 newY = Cell->y + dy;
				int32 newZ = Cell->z + dz;

				if (newX >= 0 && newX < GridManager->ElementsAmountX &&
					newY >= 0 && newY < GridManager->ElementsAmountY &&
					newZ >= 0 && newZ < GridManager->ElementsAmountZ) {

					FGridCell& Neighbour = GridManager->GetCell(newX, newY, newZ);
					if (Neighbour.Status == BURNING) {
						bool isDirectNeighbor = (dx == 0 && dy == 0 && abs(dz) == 1) ||
							(dx == 0 && dz == 0 && abs(dy) == 1) ||
							(dy == 0 && dz == 0 && abs(dx) == 1);

						bool isBottomNeighbor = (dz == -1) &&
							(abs(dx) <= 1) &&
							(abs(dy) <= 1);

						if (isDirectNeighbor) {
							directNeighborCount++;
						}
						else if (isBottomNeighbor) {
							bottomNeighborCount++;
						}
						else {
							diagonalNeighborCount++;
						}
					}
				}
			}
		}
	}

	return (4 * directNeighborCount) + (2 * diagonalNeighborCount) + (16 * bottomNeighborCount);
}


void AFireManagerActor::RestoreScene() {
	for (int32 i = 0; i < FireList.Num(); i++) {
		FGridCell* Cell = FireList[i];
		if (Cell->FireActor) {
			bool destroyed = Cell->FireActor->Destroy();
			Cell->FireActor = nullptr;
		}
	}

    for (int32 i = 0; i < BurntList.Num(); i++) {
        FGridCell* Cell = BurntList[i];
        if (Cell->OccupyingActor) {
            Cell->OccupyingActor->SetActorHiddenInGame(false);
            Cell->OccupyingActor->SetActorEnableCollision(true);
            Cell->OccupyingActor->SetActorTickEnabled(true);
            Cell->OccupyingActor->MarkComponentsRenderStateDirty();
        }
    }

}