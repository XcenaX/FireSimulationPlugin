#include "FireManagerActor.h"
#include "FireGridManager.h"
#include "FireSimulationComponent.h"
#include <MaterialData.h>
#include <Async/Async.h>
#include <MaterialDataManager.h>

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
    
    GridManager = AFireGridManager::GetInstance();
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
        if (GetWorld()) {
            UE_LOG(LogTemp, Warning, TEXT("FireManagerActor: GetWorld TRUE"));
        } else{
            UE_LOG(LogTemp, Warning, TEXT("FireManagerActor: GetWorld FALSE"));
        }
        UpdateFireSpread();
        // Сбрасываем счетчик времени
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
    }
}


void AFireManagerActor::processCheckList(int32 StartIndex, int32 EndIndex, TArray<FVector>& CoordsToRemove) {
    FScopeLock ScopeLock(&ListMutex);
    for (int32 i = StartIndex; i < EndIndex; ++i)
    {
        FGridCell Cell = CheckList[i];

        if (Cell.OccupyingActor == nullptr) {
            continue;
        }

        int32 FP = CalculateFP(GridManager->Grid, Cell.x, Cell.y, Cell.z);

        float LinearSpeed = 0.8f; // Default value

        if (Cell.OccupyingActor)
        {
            UFireSimulationComponent* FireComp = Cast<UFireSimulationComponent>(Cell.OccupyingActor->GetComponentByClass(UFireSimulationComponent::StaticClass()));
            if (FireComp)
            {
                LinearSpeed = FMaterialDataManager::Get().GetMaterialData(*(FireComp->SelectedMaterial))->LinearFlameSpeed;
            }
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
            continue;
        }

        int x = cell.x;
        int y = cell.y;
        int z = cell.z;

        for (int dx = -1; dx <= 1; dx++) {
            for (int dy = -1; dy <= 1; dy++) {
                for (int dz = -1; dz <= 1; dz++) {
                    // Пропускаем саму ячейку
                    if (dx == 0 && dy == 0 && dz == 0) continue;

                    int newX = x + dx;
                    int newY = y + dy;
                    int newZ = z + dz;

                    TArray<TArray<TArray<FGridCell>>> Cells = GridManager->Grid;
                    // Проверяем, что координаты находятся в пределах сетки
                    if (newX >= 0 && newX < Cells.Num() &&
                        newY >= 0 && newY < Cells[0].Num() &&
                        newZ >= 0 && newZ < Cells[0][0].Num()) {

                        // Проверяем состояние соседней ячейки и наличие в ней актора
                        if (Cells[newX][newY][newZ].Status < BURNING && Cells[newX][newY][newZ].OccupyingActor != nullptr) {
                            CheckList.Add(Cells[newX][newY][newZ]);
                        }
                    }
                }
            }
        }


        cell.Status = BURNING;
        FireList.Add(cell);
        CoordsToRemove.Add(FVector(cell.x, cell.y, cell.z));
        GridManager->CreateFireActor(cell, GetWorld()); // Создает актор огня в этой ячейке
    }

}

void AFireManagerActor::processFireList(int32 StartIndex, int32 EndIndex, TArray<FVector>& CoordsToRemove) {
    FScopeLock ScopeLock(&ListMutex);
    for (int32 i = StartIndex; i < EndIndex; ++i) {
        FGridCell cell = FireList[i];

        if (cell.OccupyingActor == nullptr) {
            continue;            
        }

        UFireSimulationComponent* FireComp = Cast<UFireSimulationComponent>(cell.OccupyingActor->GetComponentByClass(UFireSimulationComponent::StaticClass()));

        if (FireComp->IsWall) {
            continue;
        }

        if (cell.Status == BURNING) {
            FireList[i].time += 1;
            const FMaterialData * SelectedMaterial = FMaterialDataManager::Get().GetMaterialData(*FireComp->SelectedMaterial);

            float A = 1.05 * SelectedMaterial->BurningRate * pow(SelectedMaterial->LinearFlameSpeed, 2);
            float burntMass = A * pow(cell.time, 3);
            
            UE_LOG(LogTemp, Warning, TEXT("Burning rate: %f; FlameSpeed: %f; BurnMass: %f / %f; Time: %d"), SelectedMaterial->BurningRate, SelectedMaterial->LinearFlameSpeed, burntMass, cell.mass, cell.time);
            
            if (cell.mass <= burntMass) {
                cell.Status = BURNT;
                GridManager->ActorCellsCount[FireList[i].OccupyingActor]--;

                UE_LOG(LogTemp, Warning, TEXT("CELLS COUNT: %d;"), GridManager->ActorCellsCount[FireList[i].OccupyingActor]);
                
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
    FScopeLock ScopeLock(&ListMutex); // Используем FScopeLock для безопасного доступа к данным в многопоточной среде

    for (int32 Index = List.Num() - 1; Index >= 0; --Index)
    {
        FGridCell& Cell = List[Index];
        FVector CellCoords(Cell.x, Cell.y, Cell.z);

        if (CoordsToRemove.Contains(CellCoords))
        {
            List.RemoveAt(Index);
            CoordsToRemove.Remove(CellCoords);
        }
    }
}


int AFireManagerActor::CalculateFP(const TArray<TArray<TArray<FGridCell>>> Cells, int x, int y, int z) {
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
                if (newX >= 0 && newX < Cells.Num() && newY >= 0 && newY < Cells[0].Num() && newZ >= 0 && newZ < Cells[0][0].Num()) {
                    // Проверяем состояние соседней ячейки
                    if (Cells[newX][newY][newZ].Status == BURNING) {
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

    for (int i = 0; i < GridSizeX; ++i) {
        int GridSizeY = GridManager->Grid[i].Num();
        for (int j = 0; j < GridSizeY; ++j) {
            int GridSizeZ = GridManager->Grid[i][j].Num();
            for (int k = 0; k < GridSizeZ; ++k) {
                FGridCell& Cell = GridManager->Grid[i][j][k];
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