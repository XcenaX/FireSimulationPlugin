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

void UFireGridManager::InitializeGrid(int32 CubesPerDimension)
{
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

void UFireGridManager::DrawGrid(AActor* GridActor, UWorld* World)
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



void UFireGridManager::PopulateGridWithActors(UWorld* World)
{
    if (!World || ElementsAmount <= 0) return;

    AActor* GridActor = nullptr;
    for (TActorIterator<AActor> It(World); It; ++It)
    {
        if (It->FindComponentByClass<UBoxComponent>()) // Предполагаем, что актор сетки имеет UBoxComponent
        {
            GridActor = *It;
            break; // Берём первого найденного актора
        }
    }

    if (!GridActor) return;

    UBoxComponent* GridBounds = GridActor->FindComponentByClass<UBoxComponent>();
    if (!GridBounds) return;

    FVector GridSize = GridBounds->GetScaledBoxExtent() * 2;

    FVector CellSize(
        GridSize.X / ElementsAmount,
        GridSize.Y / ElementsAmount,
        GridSize.Z / ElementsAmount
    );


    // Очистка сетки перед заполнением
    Grid.SetNum(ElementsAmount);
    for (int32 i = 0; i < ElementsAmount; ++i)
    {
        Grid[i].SetNum(ElementsAmount);
        for (int32 j = 0; j < ElementsAmount; ++j)
        {
            Grid[i][j].SetNum(ElementsAmount);
        }
    }

    FVector GridOrigin = GridBounds->GetComponentLocation() - GridBounds->GetScaledBoxExtent();

    FCollisionQueryParams QueryParams;
    QueryParams.bTraceComplex = true;
    QueryParams.bReturnPhysicalMaterial = false;

    for (int32 i = 0; i < ElementsAmount; ++i)
    {
        for (int32 j = 0; j < ElementsAmount; ++j)
        {
            for (int32 k = 0; k < ElementsAmount; ++k)
            {
                FVector CellCenter = GridOrigin + FVector(i * CellSize.X + CellSize.X / 2, j * CellSize.Y + CellSize.Y / 2, k * CellSize.Z + CellSize.Z / 2);
                TArray<FHitResult> HitResults;
                World->SweepMultiByChannel(HitResults, CellCenter, CellCenter, FQuat::Identity, ECC_Visibility, FCollisionShape::MakeBox(CellSize / 2), QueryParams);

                for (const FHitResult& Hit : HitResults)
                {
                    AActor* Actor = Hit.GetActor();
                    if (Actor && Actor->FindComponentByClass<UFireSimulationComponent>())
                    {
                        Grid[i][j][k].OccupyingActor = Actor;
                        break; // Прекращаем поиск после первого найденного актора с компонентом
                    }
                }
            }
        }
    }
}
