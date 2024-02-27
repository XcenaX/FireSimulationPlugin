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

void UFireGridManager::InitializeGrid(int32 CubesPerDimension, int32 NewThreads)
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

                DrawDebugBox(World, CellCenter, CellSize / 2, FColor::Green, false, 5.0f, 0, 2);

                // LOGS
                if (Grid[x][y][z].OccupyingActor != nullptr)
                {
                    LogText += Grid[x][y][z].OccupyingActor->GetName();
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
    // LOGS
    FString FilePath = FPaths::ProjectDir() / TEXT("GridLog.txt");
    FFileHelper::SaveStringToFile(LogText, *FilePath);
}

TArray<FGridCell> UFireGridManager::GetBurningCells() {
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


void UFireGridManager::CreateFireActor(FGridCell Cell)
{
    UWorld* World = GEditor->GetEditorWorldContext().World();

    if (!FireActor || !World)
    {
        return;
    }

    AGridActor* GridActor = nullptr;
    for (TActorIterator<AGridActor> It(World); It; ++It)
    {
        GridActor = *It;
        break;
    }

    UBoxComponent* BoxComponent = GridActor->FindComponentByClass<UBoxComponent>();

    FVector GridSize = BoxComponent->GetScaledBoxExtent() * 2; // Получаем полные размеры сетки
    FVector CellSize(GridSize.X / ElementsAmount, GridSize.Y / ElementsAmount, GridSize.Z / ElementsAmount);
    FVector GridOrigin = BoxComponent->GetComponentLocation() - GridSize / 2; // Начальная точка сетки

    FVector CellCenter = GridOrigin + FVector(Cell.x * CellSize.X, Cell.y * CellSize.Y, Cell.z * CellSize.Z) + CellSize / 2;


    FActorSpawnParameters SpawnParams;
    FRotator Rotation(0);
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
    AActor* SpawnedActor = World->SpawnActor<AActor>(FireActor, CellCenter, Rotation, SpawnParams);

    FBox ActorBounds = SpawnedActor->GetComponentsBoundingBox(true);
    FVector ActorSize = ActorBounds.GetSize();

    // Вычисление коэффициента масштабирования для каждого измерения
    float ScaleX = CellSize.X / ActorSize.X;
    float ScaleY = CellSize.Y / ActorSize.Y;
    float ScaleZ = CellSize.Z / ActorSize.Z;

    // Выбор минимального коэффициента масштабирования для сохранения пропорций
    float UniformScaleFactor = FMath::Min(ScaleX, FMath::Min(ScaleY, ScaleZ));

    // Проверка, требуется ли масштабирование (если актор уже помещается в ячейку, его размер не изменяется)
    if (UniformScaleFactor < 1.0f)
    {
        // Применение одинакового масштабирования к актору для сохранения пропорций
        SpawnedActor->SetActorScale3D(FVector(UniformScaleFactor));
    }

    Cell.FireActor = SpawnedActor;
}

void UFireGridManager::RemoveBurntActor(FGridCell Cell) {
    for (const auto& ElemX : Grid) {
        for (const auto& ElemY : ElemX) {
            for (const auto& ElemZ : ElemY) {
                if (ElemZ.OccupyingActor == Cell.OccupyingActor) {
                    Cell.FireActor->Destroy();
                }
            }
        }
    }

    Cell.OccupyingActor->Destroy();
}