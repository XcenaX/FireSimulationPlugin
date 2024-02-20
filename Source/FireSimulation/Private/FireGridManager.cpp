#include "FireGridManager.h"
#include "Engine/World.h"

UFireGridManager* UFireGridManager::Instance = nullptr;

UFireGridManager* UFireGridManager::GetInstance()
{
    if (!Instance)
    {
        Instance = NewObject<UFireGridManager>();
        Instance->AddToRoot(); // Предотвратить уничтожение сборщиком мусора
    }
    return Instance;
}

void UFireGridManager::InitializeGrid(float CellSize)
{
    if (CellSize <= 0)
    {
        // Вывод лога ошибки
        UE_LOG(LogFireSimulation, Warning, TEXT("Cell Size must be greater than 0."));
        return;
    }

    GridCellSize = CellSize;

    // Здесь логика инициализации размера сетки и самой сетки
    // Например, если мы имеем дело с ограниченным миром
    FVector WorldSize = FVector(10000.0f); // Пример размера мира

    int32 GridSizeX = FMath::CeilToInt(WorldSize.X / CellSize);
    int32 GridSizeY = FMath::CeilToInt(WorldSize.Y / CellSize);
    int32 GridSizeZ = FMath::CeilToInt(WorldSize.Z / CellSize);

    Grid.SetNum(GridSizeX);
    for (int32 i = 0; i < GridSizeX; ++i)
    {
        Grid[i].SetNum(GridSizeY);
        for (int32 j = 0; j < GridSizeY; ++j)
        {
            Grid[i][j].SetNum(GridSizeZ);
        }
    }
}

void UFireGridManager::PopulateGridWithActors()
{
    // Очистка сетки перед заполнением
    for (auto& Column : Grid)
    {
        for (auto& Row : Column)
        {
            for (FGridCell& Cell : Row)
            {
                Cell.OccupyingActor = nullptr;
            }
        }
    }

    // Получение всех акторов с компонентом FireSimulationComponent в мире
    for (TActorIterator<AActor> It(GetWorld()); It; ++It)
    {
        AActor* Actor = *It;
        UFireSimulationComponent* FireComp = Actor->FindComponentByClass<UFireSimulationComponent>();
        if (FireComp)
        {
            FVector ActorLocation = Actor->GetActorLocation();
            int32 x, y, z;
            if (GetCellIndex(ActorLocation, x, y, z))
            {
                Grid[x][y][z].OccupyingActor = Actor;
            }
        }
    }
}


bool UFireGridManager::GetCellIndex(const FVector& Location, int32& OutX, int32& OutY, int32& OutZ) const
{
    OutX = FMath::FloorToInt(Location.X / GridCellSize);
    OutY = FMath::FloorToInt(Location.Y / GridCellSize);
    OutZ = FMath::FloorToInt(Location.Z / GridCellSize);

    // Проверка, что индексы находятся в пределах сетки
    return OutX >= 0 && OutX < Grid.Num() && OutY >= 0 && OutY < Grid[OutX].Num() && OutZ >= 0 && OutZ < Grid[OutX][OutY].Num();
}