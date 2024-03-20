#include "FireManagerActor.h"
#include "FireGridManager.h"
#include "FogManagerActor.h"
#include "FireSimulationComponent.h"
#include <MaterialData.h>
#include <Async/Async.h>
#include <MaterialDataManager.h>
#include <FogManagerActor.h>
#include "Misc/DateTime.h"
#include "HAL/PlatformTime.h"

// Sets default values
AFireManagerActor::AFireManagerActor()
{
    // Set this actor to call Tick() every frame. You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    FogManager = AFogManagerActor::GetInstance();
    GridManager = AFireGridManager::GetInstance();

}

// Called when the game starts or when spawned
void AFireManagerActor::BeginPlay()
{
    Super::BeginPlay();

    FogManager->InitializeGraph(GetWorld());    

    Threads = GridManager->Threads;

    InitializeFireSpread();

    FEditorDelegates::EndPIE.AddUObject(this, &AFireManagerActor::OnEndPIE);
}

// После завершения игры в редакторе возвращаем все сгоревшие акторы на место и тушим пожар
void AFireManagerActor::OnEndPIE(const bool bIsSimulating)
{
    UE_LOG(LogTemp, Warning, TEXT("GAME ENDED"));
    RestoreScene();
}

// Called every frame
void AFireManagerActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Суммируем прошедшее время
    TimeAccumulator += DeltaTime;

    // Проверяем, прошла ли секунда
    if (TimeAccumulator >= 1.0f)
    {
        AsyncTask(ENamedThreads::GameThread, [this]() {
            UpdateFireSpread();
        });
        TimeAccumulator -= 1.0f;
    }    
}

void AFireManagerActor::InitializeFireSpread()
{    
    // Переносим изначально горящие акторы в список для дальнейшей обработки    
    TArray<FGridCell> BurningCells = GridManager->GetBurningCells();
    NewList.Empty(BurningCells.Num());
    for (int i = 0; i < BurningCells.Num(); i++) {
        NewList.Add(BurningCells[i]);
    }
}

void AFireManagerActor::UpdateFireSpread()
{
    UE_LOG(LogTemp, Warning, TEXT("CheckList: %d; FireList: %d; NewList: %d"), CheckList.Num(), FireList.Num(), NewList.Num());
    if (CheckList.Num() > 0 || NewList.Num() > 0 || FireList.Num() > 0) {

        double Start = FPlatformTime::Seconds();

        if (CheckList.Num() > 500) {
            //parallelProcessList(CheckList, &AFireManagerActor::processCheckList, CheckListRemovalIndices);
            parallelProcessList(CheckList, [this](int32 Start, int32 End, TArray<FVector>& CoordsToRemove) {
                this->processCheckList(Start, End, CoordsToRemove);
                }, CheckListRemovalIndices);

        }
        else {
            processCheckList(0, CheckList.Num(), CheckListRemovalIndices);
        }
        RemoveCellsByCoords(CheckList, CheckListRemovalIndices);

        double End = FPlatformTime::Seconds();
        double ElapsedSeconds = End - Start;
        UE_LOG(LogTemp, Warning, TEXT("CheckList: %f сек"), ElapsedSeconds);

        Start = FPlatformTime::Seconds();

        if (NewList.Num() > 500) {
            //parallelProcessList(NewList, &AFireManagerActor::processNewList, NewListRemovalIndices);
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
        UE_LOG(LogTemp, Warning, TEXT("NewList: %f сек"), ElapsedSeconds);

        Start = FPlatformTime::Seconds();


        if (FireList.Num() > 500) {
            //parallelProcessList(FireList, &AFireManagerActor::processFireList, FireListRemovalIndices);
            parallelProcessList(FireList, [this](int32 Start, int32 End, TArray<FVector>& CoordsToRemove) {
                this->processFireList(Start, End, CoordsToRemove);
                }, FireListRemovalIndices);
        }
        else {
            processFireList(0, FireList.Num(), FireListRemovalIndices);
        }
        RemoveCellsByCoords(FireList, FireListRemovalIndices);

        End = FPlatformTime::Seconds();
        ElapsedSeconds = End - Start;
        UE_LOG(LogTemp, Warning, TEXT("FireList: %f сек"), ElapsedSeconds);
    }
}

bool AFireManagerActor::Contains(TArray<FGridCell> List, FGridCell Cell) {
    for (FGridCell Item : List) {
        if (Item == Cell) {
            return true;
        }
    }
    return false;
}

void AFireManagerActor::processCheckList(int32 StartIndex, int32 EndIndex, TArray<FVector>& CoordsToRemove) {
    FScopeLock ScopeLock(&ListMutex);
    for (int32 i = StartIndex; i < EndIndex; ++i)
    {
        FGridCell Cell = CheckList[i];

        if (Cell.OccupyingActor == nullptr || Cell.Status > EMPTY) {
            CoordsToRemove.Add(FVector(Cell.x, Cell.y, Cell.z));
            continue;
        }

        int32 FP = CalculateFP(Cell.x, Cell.y, Cell.z);
        
        float LinearSpeed = 0.8f; // Default value

        UFireSimulationComponent* FireComp = GridManager->ActorToFireCompMap.FindRef(Cell.OccupyingActor);
        if (FireComp)
        {
            const FMaterialData* Material = FMaterialDataManager::Get().GetMaterialData(*(FireComp->SelectedMaterial));
            if (!Material) continue;
            LinearSpeed = Material->LinearFlameSpeed;
        }
        
        float Probability = (LinearSpeed * FP) / 4.0;

        // UE_LOG(LogTemp, Warning, TEXT("LinearSpeed: %f; Probability: %f;"), LinearSpeed, Probability);

        if (FMath::RandRange(0.0f, 1.0f) < Probability)
        {            
            NewList.Add(Cell);
            CoordsToRemove.Add(FVector(Cell.x, Cell.y, Cell.z));
        }
    }
}

void AFireManagerActor::processNewList(int32 StartIndex, int32 EndIndex, TArray<FVector>& CoordsToRemove) {
    FScopeLock ScopeLock(&ListMutex);
    for (int32 i = StartIndex; i < EndIndex; ++i) {
        FGridCell cell = NewList[i];
        
        if (cell.OccupyingActor == nullptr) {
            CoordsToRemove.Add(FVector(cell.x, cell.y, cell.z));
            continue;
        }

        UFireSimulationComponent* FireComp = GridManager->ActorToFireCompMap.FindRef(cell.OccupyingActor);

        int32 x = cell.x;
        int32 y = cell.y;
        int32 z = cell.z;

        for (int32 dx = -1; dx <= 1; dx++) {
            for (int32 dy = -1; dy <= 1; dy++) {
                for (int32 dz = -1; dz <= 1; dz++) {
                    // Пропускаем саму ячейку
                    if (dx == 0 && dy == 0 && dz == 0) continue;

                    int32 newX = x + dx;
                    int32 newY = y + dy;
                    int32 newZ = z + dz;

                    // Проверяем, что координаты находятся в пределах сетки
                    if (newX >= 0 && newX < GridManager->ElementsAmount &&
                        newY >= 0 && newY < GridManager->ElementsAmount &&
                        newZ >= 0 && newZ < GridManager->ElementsAmount) {

                        FGridCell& Cell = GridManager->GetCell(newX, newY, newZ);
                        
                        if (Cell.Status == EMPTY && Cell.OccupyingActor && !Contains(CheckList, Cell)) {
                            CheckList.Add(Cell);
                        }
                    }
                }
            }
        }

        GridManager->GetCell(cell.x, cell.y, cell.z).Status = BURNING;
        FireList.Add(cell);
        CoordsToRemove.Add(FVector(cell.x, cell.y, cell.z));
        if (cell.FireActor == nullptr) {
            AsyncTask(ENamedThreads::GameThread, [this, cell]() {
                GridManager->CreateFireActor(cell, GetWorld()); // Создает актор огня в этой ячейке
            });
        }

        // Если Комната этого актора еще не загорелась то сделать Merge            
        if (FireComp && !FogManager->GetRoomStatusForActor(cell.OccupyingActor->GetName()) && !FireComp->IsWall) {
            int32 RoomID = FogManager->GetRoomIdForActor(cell.OccupyingActor->GetName());
            if (RoomID >= 0) {
                UE_LOG(LogTemp, Warning, TEXT("MERGE ROOM : %d ; Actor: %s"), RoomID, *cell.OccupyingActor->GetName());
                FogManager->SetRoomStatus(RoomID, true);
                FogManager->graph->MergeToSourceRoom(RoomID);
            }
        }
    }

}

void AFireManagerActor::processFireList(int32 StartIndex, int32 EndIndex, TArray<FVector>& CoordsToRemove) {
    FScopeLock ScopeLock(&ListMutex);
    for (int32 i = StartIndex; i < EndIndex; ++i) {
        FGridCell cell = FireList[i];

        if (cell.OccupyingActor == nullptr) {
            continue;            
        }

        UFireSimulationComponent* FireComp = GridManager->ActorToFireCompMap.FindRef(cell.OccupyingActor);

        if (FireComp->IsWall) {
            continue;
        }

        if (cell.Status == BURNING) {
            FireList[i].time += 1;
            const FMaterialData * SelectedMaterial = FMaterialDataManager::Get().GetMaterialData(*FireComp->SelectedMaterial);

            float A = 1.05 * SelectedMaterial->BurningRate * pow(SelectedMaterial->LinearFlameSpeed, 2);
            float burntMass = A * pow(cell.time, 3);
            
            //UE_LOG(LogTemp, Warning, TEXT("Burning rate: %f; FlameSpeed: %f; BurnMass: %f / %f; Time: %d"), SelectedMaterial->BurningRate, SelectedMaterial->LinearFlameSpeed, burntMass, cell.mass, cell.time);
            
            if (cell.mass <= burntMass && FireList[i].time > 2) {
                GridManager->GetCell(cell.x, cell.y, cell.z).Status = BURNT;
                FireList[i].Status = BURNT;
                GridManager->ActorCellsCount[FireList[i].OccupyingActor]--;

                //UE_LOG(LogTemp, Warning, TEXT("CELLS COUNT: %d;"), GridManager->ActorCellsCount[FireList[i].OccupyingActor]);
                
                if (GridManager->ActorCellsCount[cell.OccupyingActor] == 0) {
                    GridManager->RemoveBurntActor(FireList[i]); // Обьект сгорел, удаляем этот актор и огонь на нем
                }
                CoordsToRemove.Add(FVector(cell.x, cell.y, cell.z));
            }
        }
    }
}

void AFireManagerActor::parallelProcessList(TArray<FGridCell>& List, TFunction<void(int32, int32, TArray<FVector>&)> ProcessFunction, TArray<FVector>& GlobalCoordsToRemove) {
    int32 TotalSize = List.Num();
    int32 MaxElementsPerTask = FMath::CeilToInt((float)TotalSize / (float)Threads);

    // Список для хранения Future результатов каждой асинхронной задачи
    TArray<TFuture<void>> Futures;

    for (int32 Index = 0; Index < Threads; ++Index) {
        int32 StartIndex = Index * MaxElementsPerTask;
        int32 EndIndex = FMath::Min(StartIndex + MaxElementsPerTask, TotalSize);

        // Запускаем асинхронную задачу
        Futures.Add(Async(EAsyncExecution::ThreadPool, [this, StartIndex, EndIndex, &List, &ProcessFunction, &GlobalCoordsToRemove]() {
            TArray<FVector> LocalCoordsToRemove;
            ProcessFunction(StartIndex, EndIndex, LocalCoordsToRemove);

            // Захватываем мьютекс для безопасного доступа к глобальному списку
            FScopeLock ScopeLock(&ListMutex);
            for (const FVector& Coord : LocalCoordsToRemove) {
                GlobalCoordsToRemove.Add(Coord);
            }
            }));
    }

    // Ожидаем завершения всех задач
    for (TFuture<void>& Future : Futures) {
        Future.Wait();
    }
}


void AFireManagerActor::RemoveCellsByCoords(TArray<FGridCell>& List, TArray<FVector>& CoordsToRemove)
{
    FScopeLock ScopeLock(&ListMutex);

    for (int32 Index = List.Num() - 1; Index >= 0; --Index)
    {
        const FGridCell& Cell = List[Index];
        const FVector CellCoords(Cell.x, Cell.y, Cell.z);

        for (const FVector& CoordToRemove : CoordsToRemove)
        {
            if (CellCoords.X == CoordToRemove.X && CellCoords.Y == CoordToRemove.Y && CellCoords.Z == CoordToRemove.Z)
            {
                List.RemoveAt(Index);
                break; // Выходим из внутреннего цикла, так как нашли соответствующую ячейку для удаления
            }
        }
    }
    CoordsToRemove.Empty();
}


int AFireManagerActor::CalculateFP(int x, int y, int z) {
    int directNeighborCount = 0; // Для прямых соседей
    int diagonalNeighborCount = 0; // Для диагональных соседей

    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            for (int dz = -1; dz <= 1; dz++) {
                // Пропускаем саму ячейку
                if (dx == 0 && dy == 0 && dz == 0) continue;

                int newX = x + dx;
                int newY = y + dy;
                int newZ = z + dz;

                // Проверяем, что координаты находятся в пределах границ
                if (newX >= 0 && newX < GridManager->ElementsAmount && newY >= 0 && newY < GridManager->ElementsAmount && newZ >= 0 && newZ < GridManager->ElementsAmount) {
                    // Проверяем состояние соседней ячейки
                    if (GridManager->GetCell(newX, newY, newZ).Status == BURNING) {
                        // Если сосед по одной из осей (прямой сосед)
                        if (dx == 0 || dy == 0 || dz == 0) {
                            directNeighborCount++;
                        }
                        else {
                            // Диагональный сосед
                            diagonalNeighborCount++;
                        }
                    }
                }
            }
        }
    }

    return 2 * directNeighborCount + diagonalNeighborCount;
}


void AFireManagerActor::RestoreScene() { // Делает невидимые(сгоревшие) акторы видимымм. Удаляет все акторы огня.
    int GridSizeX = GridManager->Grid.Num();

    UE_LOG(LogTemp, Warning, TEXT("GRID SIZE: %d"), GridSizeX);

    for (int i = 0; i < GridManager->ElementsAmount; ++i) {
        for (int j = 0; j < GridManager->ElementsAmount; ++j) {
            for (int k = 0; k < GridManager->ElementsAmount; ++k) {
                FGridCell& Cell = GridManager->GetCell(i, j, k);
                if (Cell.OccupyingActor) {                    
                    Cell.OccupyingActor->SetActorHiddenInGame(false);
                    Cell.OccupyingActor->SetActorEnableCollision(true);
                    Cell.OccupyingActor->SetActorTickEnabled(true);
                    Cell.OccupyingActor->MarkComponentsRenderStateDirty();
                }
                if (Cell.FireActor) {
                    bool destroyed = Cell.FireActor->Destroy();
                    Cell.FireActor = nullptr;
                    UE_LOG(LogTemp, Warning, TEXT("FIRE ACTOR DESTROYED: %b"), destroyed);
                }
            }
        }
    }
}