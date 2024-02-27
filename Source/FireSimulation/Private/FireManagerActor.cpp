#include "FireManagerActor.h"
#include "FireGridManager.h"
#include "FireSimulationComponent.h"
#include <MaterialData.h>
#include <Async/Async.h>

// Sets default values
AFireManagerActor::AFireManagerActor()
{
    // Set this actor to call Tick() every frame. You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
    FireManager = UFireGridManager::GetInstance();
    Threads = FireManager->Threads;
    Cells = FireManager->Grid;

}

// Called when the game starts or when spawned
void AFireManagerActor::BeginPlay()
{
    Super::BeginPlay();
    
    InitializeFireSpread();
}

// Called every frame
void AFireManagerActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    UpdateFireSpread();
}

void AFireManagerActor::InitializeFireSpread()
{
    // Переносим изначально горящие акторы в список для дальнейшей обработки
    TArray<FGridCell> BurningCells = FireManager->GetBurningCells();
    for (int i = 0; i < BurningCells.Num(); i++) {
        NewList.Add(BurningCells[i]);
    }
}

void AFireManagerActor::UpdateFireSpread()
{
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
        FGridCell& Cell = CheckList[i];

        int32 FP = CalculateFP(Cells, Cell.x, Cell.y, Cell.z);

        float LinearSpeed = 0.8f; // Default value

        if (Cell.OccupyingActor)
        {
            UFireSimulationComponent* FireComp = Cast<UFireSimulationComponent>(Cell.OccupyingActor->GetComponentByClass(UFireSimulationComponent::StaticClass()));
            if (FireComp)
            {
                FMaterialData SelectedMaterial = FireComp->SelectedMaterial;
                LinearSpeed = SelectedMaterial.LinearFlameSpeed;
            }
        }

        double Probability = (LinearSpeed * FP) / 4.0;

        if (FMath::RandRange(0.0f, 1.0f) < Probability)
        {
            NewList.Add(Cell);
            CoordsToRemove.Add(FVector(Cell.x, Cell.y, Cell.z));
        }
    }
}

void AFireManagerActor::processNewList(int32 StartIndex, int32 EndIndex, TArray<FVector>& CoordsToRemove) {
    FScopeLock ScopeLock(&ListMutex);
    for (size_t i = StartIndex; i < EndIndex; ++i) {
        FGridCell cell = CheckList[i];

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

                        UFireSimulationComponent* FireComp = Cast<UFireSimulationComponent>(Cells[newX][newY][newZ].OccupyingActor->GetComponentByClass(UFireSimulationComponent::StaticClass()));
                        bool IsWall = FireComp->IsWall;

                        // Проверяем состояние соседнего пикселя и стену на карте
                        if (Cells[newX][newY][newZ].Status < BURNING && !IsWall) {
                            CheckList.Add(Cells[newX][newY][newZ]);
                        }
                    }
                }
            }
        }

        cell.Status = BURNING;
        FireList.Add(cell);
        CoordsToRemove.Add(FVector(cell.x, cell.y, cell.z));
        FireManager->CreateFireActor(cell); // Создает актор огня в этой ячейке
    }

}

void AFireManagerActor::processFireList(int32 StartIndex, int32 EndIndex, TArray<FVector>& CoordsToRemove) {
    FScopeLock ScopeLock(&ListMutex);
    for (size_t i = StartIndex; i < EndIndex; ++i) {
        FGridCell cell = CheckList[i];

        UFireSimulationComponent* FireComp = Cast<UFireSimulationComponent>(cell.OccupyingActor->GetComponentByClass(UFireSimulationComponent::StaticClass()));
        FMaterialData SelectedMaterial = FireComp->SelectedMaterial;

        if (cell.Status == BURNING) {
            cell.time += 1;
            double A = 1.05 * SelectedMaterial.BurningRate * pow(SelectedMaterial.LinearFlameSpeed, 2);
            double burntMass = A * pow(cell.time, 3);

            if (FireComp->Mass <= burntMass) {
                cell.Status = BURNT;
                FireManager->ActorCellsCount[cell.OccupyingActor]--;
                if (FireManager->ActorCellsCount[cell.OccupyingActor] == 0) {
                    FireManager->RemoveBurntActor(cell); // Обьект сгорел, удаляем этот актор и огонь на нем
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
