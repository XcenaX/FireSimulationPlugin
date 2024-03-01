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
    
    GridManager = UFireGridManager::GetInstance();
    Threads = GridManager->Threads;
    Cells = GridManager->Grid;

    InitializeFireSpread();
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

        int32 FP = CalculateFP(Cells, Cell.x, Cell.y, Cell.z);

        float LinearSpeed = 0.8f; // Default value

        if (Cell.OccupyingActor)
        {
            UFireSimulationComponent* FireComp = Cast<UFireSimulationComponent>(Cell.OccupyingActor->GetComponentByClass(UFireSimulationComponent::StaticClass()));
            if (FireComp)
            {
                FMaterialData SelectedMaterial = FireComp->SelectedMaterialData;
                LinearSpeed = SelectedMaterial.LinearFlameSpeed;
            }
        }

        double Probability = (LinearSpeed * FP) / 4.0;

        UE_LOG(LogTemp, Warning, TEXT("LinearSpeed: %d; Probability: %d;"), LinearSpeed, Probability);

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
                    // Убедимся, что мы проверяем только по одной оси за раз
                    if (dx != 0 && dy != 0 || dx != 0 && dz != 0 || dy != 0 && dz != 0) continue;

                    // Пропускаем сам пиксель
                    if (dx == 0 && dy == 0 && dz == 0) continue;

                    int newX = x + dx;
                    int newY = y + dy;
                    int newZ = z + dz;

                    // Проверяем, что координаты находятся в пределах комнаты
                    if (newX >= 0 && newX < Cells.Num() &&
                        newY >= 0 && newY < Cells.Num() &&
                        newZ >= 0 && newZ < Cells.Num()) {

                        // Проверяем состояние соседнего пикселя и стену на карте
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
        GridManager->CreateFireActor(cell); // Создает актор огня в этой ячейке
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
            cell.time += 1;
            double A = 1.05 * FireComp->SelectedMaterialData.BurningRate * pow(FireComp->SelectedMaterialData.LinearFlameSpeed, 2);
            double burntMass = A * pow(cell.time, 3);
            
            if (FireComp->Mass <= burntMass) {
                cell.Status = BURNT;
                GridManager->ActorCellsCount[cell.OccupyingActor]--;
                if (GridManager->ActorCellsCount[cell.OccupyingActor] == 0) {
                    GridManager->RemoveBurntActor(cell); // Обьект сгорел, удаляем этот актор и огонь на нем
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


int AFireManagerActor::CalculateFP(TArray<TArray<TArray<FGridCell>>> cells, int x, int y, int z) {
    int a = 0;    
    int b = 0;

    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            for (int dz = -1; dz <= 1; dz++) {
                // Убедимся, что мы проверяем только по одной оси за раз
                if ((dx != 0 && dy != 0) || (dx != 0 && dz != 0) || (dy != 0 && dz != 0)) continue;

                // Пропускаем сам пиксель
                if (dx == 0 && dy == 0 && dz == 0) continue;

                int newX = x + dx;
                int newY = y + dy;
                int newZ = z + dz;

                // Проверяем, что координаты находятся в пределах комнаты
                if (newX >= 0 && newX < cells.Num() &&
                    newY >= 0 && newY < cells.Num() &&
                    newZ >= 0 && newZ < cells.Num()) {

                    // Проверяем состояние соседнего пикселя
                    if (cells[newX][newY][newZ].Status== BURNING) {
                        a++;
                    }
                }
            }
        }
    }

    // Дополнительно проверяем диагональные соседи (влияют вдвое меньше)
    for (int dx = -1; dx <= 1; dx += 2) {
        for (int dy = -1; dy <= 1; dy += 2) {
            for (int dz = -1; dz <= 1; dz += 2) {
                // Пропускаем центральный пиксель
                if (dx == 0 && dy == 0 && dz == 0) continue;

                int newX = x + dx;
                int newY = y + dy;
                int newZ = z + dz;

                // Проверяем, что координаты находятся в пределах комнаты
                if (newX >= 0 && newX < cells.Num() &&
                    newY >= 0 && newY < cells.Num() &&
                    newZ >= 0 && newZ < cells.Num()) {

                    // Проверяем состояние соседнего пикселя
                    if (cells[newX][newY][newZ].Status== BURNING) {
                        b++; // Влияние вдвое меньше
                    }
                }
            }
        }
    }

    return 2 * a + b;
}
