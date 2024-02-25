#include "FireGridManager.h"
#include "Engine/World.h"
#include "EngineUtils.h"
#include "DrawDebugHelpers.h"
#include "FireSimulationComponent.h"
#include "Components/BoxComponent.h"
#include <GridActor.h>
#include <Misc/FileHelper.h>

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

void UFireGridManager::InitializeGrid(int32 CubesPerDimension)
{
    ElementsAmount = CubesPerDimension;

    Grid.SetNum(CubesPerDimension);
    for (int32 i = 0; i < CubesPerDimension; ++i)
    {
        Grid[i].SetNum(CubesPerDimension);
        for (int32 j = 0; j < CubesPerDimension; ++j)
        {
            Grid[i][j].SetNum(CubesPerDimension);
        }
    }
}

void UFireGridManager::DrawGrid(bool bVisible, UWorld * World, AActor * GridActor)
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


void UFireGridManager::PopulateGridWithActors(UWorld* World, AActor * GridActor)
{
    if (!World || !GridActor || ElementsAmount <= 0) return;

    UBoxComponent* BoxComponent = GridActor->FindComponentByClass<UBoxComponent>();
    if (!BoxComponent) return;

    FVector GridSize = BoxComponent->GetScaledBoxExtent() * 2; // Получаем полные размеры сетки

    float CellSizeX = (GridSize.X * 2) / ElementsAmount;
    float CellSizeY = (GridSize.Y * 2) / ElementsAmount;
    float CellSizeZ = (GridSize.Z * 2) / ElementsAmount;
    FVector CellSizeVector(CellSizeX, CellSizeY, CellSizeZ);

    FVector CellSize = GridSize / CellSizeVector; // Размер одной ячейки в каждом измерении

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
                World->SweepMultiByChannel(HitResults, CellCenter, CellCenter, FQuat::Identity, ECC_Visibility, Box, Params);

                for (const FHitResult& Hit : HitResults)
                {
                    if (AActor* HitActor = Hit.GetActor())
                    {
                        LogText += "(has hit)";
                        if (HitActor->FindComponentByClass<UFireSimulationComponent>())
                        {
                            Grid[x][y][z].OccupyingActor = HitActor;
                            break; // Прекращаем поиск после первого найденного актора
                        }
                    }
                }

                // LOGS
                if (Grid[x][y][z].OccupyingActor != nullptr)
                {
                    LogText += Grid[x][y][z].OccupyingActor->GetName();
                }
                else
                {
                    LogText += "NoActor";
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
    // LOGS
    FString FilePath = FPaths::ProjectDir() / TEXT("GridLog.txt");
    FFileHelper::SaveStringToFile(LogText, *FilePath);
}
