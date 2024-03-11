#include "FireGridManager.h"
#include "Engine/World.h"
#include "EngineUtils.h"
#include "DrawDebugHelpers.h"
#include "FireSimulationComponent.h"
#include "Components/BoxComponent.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include <GridActor.h>
#include <Misc/FileHelper.h>
#include <FogManagerActor.h>
#include <DoorComponent.h>

AFireGridManager* AFireGridManager::Instance = nullptr;

AFireGridManager::AFireGridManager()
{
	// Инициализация переменных и состояний по умолчанию
}

AFireGridManager* AFireGridManager::GetInstance()
{
	if (!Instance)
	{
		Instance = NewObject<AFireGridManager>();
		Instance->AddToRoot(); // Предотвратить уничтожение сборщиком мусора
	}
	return Instance;
}

void AFireGridManager::InitializeGrid(int32 CubesPerDimension, int32 NewThreads)
{
	ElementsAmount = CubesPerDimension;
	Threads = NewThreads;

	Grid.SetNum(CubesPerDimension);
	for (int32 i = 0; i < CubesPerDimension; ++i)
	{
		Grid[i].SetNum(CubesPerDimension);
		for (int32 j = 0; j < CubesPerDimension; ++j)
		{
			Grid[i][j].SetNum(CubesPerDimension);
			for (int32 k = 0; k < CubesPerDimension; k++) {
				Grid[i][j][k].x = i;
				Grid[i][j][k].y = j;
				Grid[i][j][k].z = k;

				Grid[i][j][k].OccupyingActor = nullptr;
			}
		}
	}

	ActorCellsCount.Empty();
}

void AFireGridManager::DrawGrid(bool bVisible, UWorld* World, AActor* GridActor)
{
	if (!GridActor || !World) return;

	UBoxComponent* BoxComponent = Cast<UBoxComponent>(GridActor->GetComponentByClass(UBoxComponent::StaticClass()));
	if (!BoxComponent) return;

	FVector Origin = BoxComponent->GetComponentLocation();
	FVector BoxExtent = BoxComponent->GetScaledBoxExtent();

	// Рассчитываем размер ячейки для каждого измерения
	float CellSizeX = (BoxExtent.X * 2) / ElementsAmount;
	float CellSizeY = (BoxExtent.Y * 2) / ElementsAmount;
	float CellSizeZ = (BoxExtent.Z * 2) / ElementsAmount;

	FlushPersistentDebugLines(World);

	// Рисование сетки
	for (int x = 0; x < ElementsAmount; ++x)
	{
		for (int y = 0; y < ElementsAmount; ++y)
		{
			for (int z = 0; z < ElementsAmount; ++z)
			{
				FVector CellOrigin = Origin + FVector(x * CellSizeX, y * CellSizeY, z * CellSizeZ) - BoxExtent + FVector(CellSizeX / 2, CellSizeY / 2, CellSizeZ / 2);
				DrawDebugBox(World, CellOrigin, FVector(CellSizeX / 2, CellSizeY / 2, CellSizeZ / 2), FColor::Blue, true, -1.f, 0, 1);
			}
		}
	}
}


void AFireGridManager::PopulateGridWithActors(UWorld* World, AActor* GridActor)
{
	if (!World || !GridActor || ElementsAmount <= 0) return;

	UBoxComponent* BoxComponent = GridActor->FindComponentByClass<UBoxComponent>();
	if (!BoxComponent) return;

    FVector GridSize = BoxComponent->GetScaledBoxExtent() * 2; // Получаем полные размеры 
    FVector CellSize(GridSize.X / ElementsAmount, GridSize.Y / ElementsAmount, GridSize.Z / ElementsAmount);


	// Очищаем и инициализируем сетку
	Grid.SetNum(ElementsAmount);
	for (int i = 0; i < ElementsAmount; ++i)
	{
		Grid[i].SetNum(ElementsAmount);
		for (int j = 0; j < ElementsAmount; ++j)
		{
			Grid[i][j].SetNum(ElementsAmount);
		}
	}

	// Заполняем сетку акторами
	FVector GridOrigin = BoxComponent->GetComponentLocation() - GridSize / 2; // Начальная точка сетки
	FCollisionQueryParams Params;
	Params.bTraceComplex = true;
	Params.bReturnPhysicalMaterial = false;

	FString LogText;
	for (int x = 0; x < ElementsAmount; ++x)
	{
		for (int y = 0; y < ElementsAmount; ++y)
		{
			for (int z = 0; z < ElementsAmount; ++z)
			{
				FVector CellCenter = GridOrigin + FVector(x * CellSize.X, y * CellSize.Y, z * CellSize.Z) + CellSize / 2;
				FCollisionShape Box = FCollisionShape::MakeBox(CellSize / 2);
				TArray<FHitResult> HitResults;
				World->SweepMultiByChannel(HitResults, CellCenter, CellCenter, FQuat::Identity, ECC_WorldStatic, Box, Params);

				for (const FHitResult& Hit : HitResults)
				{
					if (AActor* HitActor = Hit.GetActor())
					{
						if (HitActor->FindComponentByClass<UFireSimulationComponent>())
						{
							Grid[x][y][z].OccupyingActor = HitActor;
							Grid[x][y][z].Status = BURNING;

							if (!HitActor->FindComponentByClass<UFireSimulationComponent>()->IsBurning) {
								Grid[x][y][z].Status = EMPTY;
							}

							if (ActorCellsCount.Contains(HitActor))
							{
								ActorCellsCount[HitActor]++;
							}
							else
							{
								ActorCellsCount.Add(HitActor, 1);
							}

							break; // Прекращаем поиск после первого найденного актора
						}
					}
				}

				// LOGS
				if (Grid[x][y][z].OccupyingActor != nullptr)
				{
					LogText += "O";//Grid[x][y][z].OccupyingActor->GetName();
				}
				else
				{
					LogText += "*";
				}

				if (z < Grid[x][y].Num() - 1)
				{
					LogText += ", ";
				}
			}
			LogText += "\n";
		}
		LogText += "-\n";
	}

	for (int x = 0; x < ElementsAmount; ++x)
	{
		for (int y = 0; y < ElementsAmount; ++y)
		{
			for (int z = 0; z < ElementsAmount; ++z)
			{
				if (Grid[x][y][z].OccupyingActor != nullptr) {
					UFireSimulationComponent* FireComp = Cast<UFireSimulationComponent>(Grid[x][y][z].OccupyingActor->GetComponentByClass(UFireSimulationComponent::StaticClass()));
					Grid[x][y][z].mass = FireComp->Mass / ActorCellsCount[Grid[x][y][z].OccupyingActor];
				}
			}
		}
	}


	// LOGS
	FString FilePath = FPaths::ProjectDir() / TEXT("GridLog.txt");
	FFileHelper::SaveStringToFile(LogText, *FilePath);
}

TArray<FGridCell> AFireGridManager::GetBurningCells() {
	TArray<FGridCell> BurningCells;
	for (int i = 0; i < Grid.Num(); i++) {
		for (int j = 0; j < Grid.Num(); j++) {
			for (int k = 0; k < Grid.Num(); k++) {
				if (Grid[i][j][k].Status == BURNING) {
					BurningCells.Add(Grid[i][j][k]);
				}
			}
		}
	}
	return BurningCells;
}


void AFireGridManager::CreateFireActor(FGridCell Cell, UWorld* World)
{
	// UWorld* World = GEditor->GetEditorWorldContext().World();
	// UWorld* World = GetWorld();

	if (!SelectedParticleFire || !World)
	{
		UE_LOG(LogTemp, Warning, TEXT("VLAD! NO WORLD!"));
		return;
	}

	AGridActor* GridActor = nullptr;
	for (TActorIterator<AGridActor> It(World); It; ++It)
	{
		GridActor = *It;
		break;
	}

	// Вычисляем локацию ячейки
	UBoxComponent* BoxComponent = GridActor->FindComponentByClass<UBoxComponent>();

	FVector GridSize = BoxComponent->GetScaledBoxExtent() * 2; // Получаем полные размеры сетки
	FVector CellSize(GridSize.X / ElementsAmount, GridSize.Y / ElementsAmount, GridSize.Z / ElementsAmount);
	FVector GridOrigin = BoxComponent->GetComponentLocation() - GridSize / 2; // Начальная точка сетки

	FVector CellCenter = GridOrigin + FVector(Cell.x * CellSize.X, Cell.y * CellSize.Y, Cell.z * CellSize.Z) + CellSize / 2;

	// Создаем актор огня
	FActorSpawnParameters SpawnParams;
	FRotator Rotation(0);
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	AActor* SpawnedActor = World->SpawnActor<AActor>(AActor::StaticClass(), CellCenter, Rotation, SpawnParams);

	UParticleSystem* SelectedParticleSystem = Cast<UParticleSystem>(SelectedParticleFire);
	//UParticleSystemComponent* ParticleSystemComponent = UGameplayStatics::SpawnEmitterAtLocation(World, SelectedParticleSystem, CellCenter, Rotation);

	// ДОбавляем компонент ParticleSystem к актору
	UParticleSystemComponent* ParticleSystemComponent = NewObject<UParticleSystemComponent>(SpawnedActor, UParticleSystemComponent::StaticClass());
	SpawnedActor->AddInstanceComponent(ParticleSystemComponent);
	ParticleSystemComponent->SetTemplate(SelectedParticleSystem);
	ParticleSystemComponent->RegisterComponent(); // Регистрация компонента 
	ParticleSystemComponent->SetWorldLocation(CellCenter);

	// FBox ActorBounds = SpawnedActor->GetComponentsBoundingBox(true);
	// FVector ActorSize = ActorBounds.GetSize();

	FBoxSphereBounds Bounds = ParticleSystemComponent->Bounds;
	FVector BoxExtent = Bounds.BoxExtent; // Половины размеров ограничивающего объема во всех трех направлениях
	FVector SphereRadius = FVector(Bounds.SphereRadius); // Радиус ограничивающего сферы

	// Вычисление коэффициента масштабирования для каждого измерения
	float ScaleX = CellSize.X / SphereRadius.X;
	float ScaleY = CellSize.Y / SphereRadius.Y;
	float ScaleZ = CellSize.Z / SphereRadius.Z;

	// Выбор минимального коэффициента масштабирования для сохранения пропорций
	float UniformScaleFactor = FMath::Min(ScaleX, FMath::Min(ScaleY, ScaleZ));

	// Проверка, требуется ли масштабирование (если актор уже помещается в ячейку, его размер не изменяется)
	if (UniformScaleFactor < 1.0f)
	{
		// Применение одинакового масштабирования к актору для сохранения пропорций
		ParticleSystemComponent->SetWorldScale3D(FVector(UniformScaleFactor * 2));
	}
	ParticleSystemComponent->SetVisibility(true);
	ParticleSystemComponent->Activate();
	SpawnedActor->RegisterAllComponents();


	Cell.FireActor = SpawnedActor;
}

void AFireGridManager::RemoveBurntActor(FGridCell& Cell) {
	int GridSizeX = Grid.Num();
	for (int i = 0; i < GridSizeX; ++i) {
		int GridSizeY = Grid[i].Num();
		for (int j = 0; j < GridSizeY; ++j) {
			int GridSizeZ = Grid[i][j].Num();
			for (int k = 0; k < GridSizeZ; ++k) {
				if (Grid[i][j][k].OccupyingActor == Cell.OccupyingActor && Cell.FireActor) {
					Cell.FireActor->Destroy();
					Cell.FireActor = nullptr;
				}
			}
		}
	}

    if (Cell.OccupyingActor) {
        UDoorComponent* DoorComp = Cast<UDoorComponent>(Cell.OccupyingActor->GetComponentByClass(UDoorComponent::StaticClass()));
        if (AFogManagerActor::GetInstance() && AFogManagerActor::GetInstance()->graph) {
            AFogManagerActor::GetInstance()->graph->MergeToSourceRoom(DoorComp->ConnectedRoom2->RoomID);
        }

		Cell.OccupyingActor->SetActorHiddenInGame(true);
		Cell.OccupyingActor->SetActorEnableCollision(false);
		Cell.OccupyingActor->SetActorTickEnabled(false);
		Cell.OccupyingActor->MarkComponentsRenderStateDirty();
	}
}