#include "FireGridManager.h"
#include "Engine/World.h"
#include "EngineUtils.h"
#include "DrawDebugHelpers.h"
#include "UnrealEd.h"
#include "FireSimulationComponent.h"

UFireGridManager* UFireGridManager::Instance = nullptr;

UFireGridManager::UFireGridManager()
{
    // Инициализация переменных и состояний по умолчанию
}

UFireGridManager* UFireGridManager::GetInstance()
{
    if (!Instance)
    {
        Instance = NewObject<UFireGridManager>();
        Instance->AddToRoot(); // Предотвратить уничтожение сборщиком мусора
    }
    return Instance;
}

void UFireGridManager::InitializeGrid(int32 CubesPerDimension, float GridLength, const FVector& NewGridOrigin)
{
    GridCellSize = GridLength / CubesPerDimension;

    Grid.SetNum(CubesPerDimension);
    for (int32 i = 0; i < CubesPerDimension; ++i)
    {
        Grid[i].SetNum(CubesPerDimension);
        for (int32 j = 0; j < CubesPerDimension; ++j)
        {
            Grid[i][j].SetNum(CubesPerDimension);
        }
    }

    // Установка начала координат сетки
    this->GridOrigin = NewGridOrigin;
}

void UFireGridManager::DrawGrid(bool bVisible)
{
    UWorld* World = GEditor->GetEditorWorldContext().World();
    FlushPersistentDebugLines(World);

    if (!bVisible)
    {        
        return;
    }

    for (int32 i = 0; i < Grid.Num(); ++i)
    {
        for (int32 j = 0; j < Grid[i].Num(); ++j)
        {
            for (int32 k = 0; k < Grid[i][j].Num(); ++k)
            {
                FVector Center = GridOrigin + FVector(i * GridCellSize, j * GridCellSize, k * GridCellSize) + FVector(GridCellSize / 2);
                DrawDebugBox(World, Center, FVector(GridCellSize / 2), FColor::Red, true, -1.0f, 0, 2);
            }
        }
    }
}


void UFireGridManager::PopulateGridWithActors(UWorld* World)
{
    if (!World) return;

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

    for (TActorIterator<AActor> It(World); It; ++It)
    {
        AActor* Actor = *It;
        UFireSimulationComponent* FireComp = Actor->FindComponentByClass<UFireSimulationComponent>();
        if (FireComp)
        {
            FVector ActorLocation = Actor->GetActorLocation();
            int32 x, y, z;
            if (GetCellIndex(ActorLocation, x, y, z))
            {
                // Убедитесь, что массив Grid инициализирован и имеет достаточный размер перед обращением к Grid[x][y][z]
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