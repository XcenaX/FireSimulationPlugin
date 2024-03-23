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
#include <MaterialDataManager.h>

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

void AFireGridManager::InitializeGrid(int32 CubesPerDimension, int32 NewThreads, int32 FireSize)
{
	ElementsAmount = CubesPerDimension;
	Threads = NewThreads;
	FireParticleSize = FireSize;

	Grid.Empty();
	for (int32 i = 0; i < ElementsAmount; i++)
	{
		for (int32 j = 0; j < ElementsAmount; j++)
		{
			for (int32 k = 0; k < ElementsAmount; k++) {
				FGridCell Cell;

				Cell.x = i;
				Cell.y = j;
				Cell.z = k;

				Grid.Add(Cell);
			}			
		}
	}

	for (int32 i = 0; i < ElementsAmount; i++)
	{
		for (int32 j = 0; j < ElementsAmount; j++)
		{
			for (int32 k = 0; k < ElementsAmount; k++) {
				FGridCell& CurrentCell = GetCell(i, j, k);

				for (int32 dx = -1; dx <= 1; dx++) {
					for (int32 dy = -1; dy <= 1; dy++) {
						for (int32 dz = -1; dz <= 1; dz++) {
							// Пропускаем саму ячейку
							if (dx == 0 && dy == 0 && dz == 0) continue;

							int32 newX = i + dx;
							int32 newY = j + dy;
							int32 newZ = k + dz;

							// Проверяем, что координаты находятся в пределах сетки
							if (newX >= 0 && newX < ElementsAmount &&
								newY >= 0 && newY < ElementsAmount &&
								newZ >= 0 && newZ < ElementsAmount) {

								FGridCell& NeighbourCell = GetCell(newX, newY, newZ);
								CurrentCell.Neighbours.Add(&NeighbourCell);
							}
						}
					}
				}

			}
		}
	}	

	ActorCellsCount.Empty();
}

void AFireGridManager::DrawGrid(bool bVisible, UWorld* World, AActor* NewGridActor)
{
	if (!NewGridActor || !World) return;

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

void AFireGridManager::ClearGrid() {
	Grid.Empty();
}

FGridCell& AFireGridManager::GetCell(int32 x, int32 y, int32 z) {
	int32 index = z + ElementsAmount * (y + ElementsAmount * x);
	return Grid[index];
}

void AFireGridManager::PopulateGridWithActors(UWorld* World, AActor* NewGridActor)
{
	if (!World || !NewGridActor || ElementsAmount <= 0) return;

	GridActor = Cast<AGridActor>(NewGridActor);

	UBoxComponent* BoxComponent = GridActor->FindComponentByClass<UBoxComponent>();
	if (!BoxComponent) return;

    FVector GridSize = BoxComponent->GetScaledBoxExtent() * 2; // Получаем полные размеры 
    FVector CellSize(GridSize.X / ElementsAmount, GridSize.Y / ElementsAmount, GridSize.Z / ElementsAmount);

	// Заполняем сетку акторами
	FVector GridOrigin = BoxComponent->GetComponentLocation() - GridSize / 2; // Начальная точка сетки	

	FCollisionQueryParams QueryParams;
	QueryParams.bReturnPhysicalMaterial = false;

	FString LogText;
	for (int32 x = 0; x < ElementsAmount; x++)
	{
		for (int32 y = 0; y < ElementsAmount; y++)
		{
			for (int32 z = 0; z < ElementsAmount; z++)
			{
				if (z + ElementsAmount * (y + ElementsAmount * x) >= pow(ElementsAmount, 3)) continue;
				
				FGridCell& Cell = GetCell(x, y, z);
				FVector CellCenter = GridOrigin + FVector(x * CellSize.X, y * CellSize.Y, z * CellSize.Z) + CellSize / 2;
				FCollisionShape Box = FCollisionShape::MakeBox(CellSize / 2);
				TArray<FOverlapResult> OverlapResults;
				World->OverlapMultiByChannel(OverlapResults, CellCenter, FQuat::Identity, ECC_WorldStatic, Box, QueryParams);
				
				AActor* PickedActor = nullptr;
				float MaxLinearFlameSpeed = 0;
				UFireSimulationComponent* PickedFireComp = nullptr;

				for (const FOverlapResult& Hit : OverlapResults)
				{
					if (AActor* HitActor = Hit.GetActor())
					{
						if (UFireSimulationComponent* FireComp = HitActor->FindComponentByClass<UFireSimulationComponent>())
						{
							const FMaterialData* Material = FMaterialDataManager::Get().GetMaterialData(FireComp->SelectedMaterial);
							if (Material && MaxLinearFlameSpeed < Material->LinearFlameSpeed) {
								MaxLinearFlameSpeed = Material->LinearFlameSpeed;
								PickedActor = HitActor;
								PickedFireComp = FireComp;
							}														
						}
					}
				}

				Cell.OccupyingActor = PickedActor;

				if (PickedActor && PickedFireComp) {
					ActorToFireCompMap.Add(PickedActor, PickedFireComp);
					Cell.Status = BURNING;

					if (!PickedFireComp->IsBurning) {
						Cell.Status = EMPTY;
					}

					if (ActorCellsCount.Contains(PickedActor))
					{
						ActorCellsCount[PickedActor]++;
					}
					else
					{
						ActorCellsCount.Add(PickedActor, 1);
					}
				}				

				// LOGS
				if (Cell.OccupyingActor)
				{
					LogText += "O";
				}
				else
				{
					LogText += "*";
				}

				if (z < ElementsAmount - 1)
				{
					LogText += ", ";
				}
			}
			LogText += "\n";
		}
		LogText += "-\n";
	}

	for (int x = 0; x < ElementsAmount; x++)
	{
		for (int y = 0; y < ElementsAmount; y++)
		{
			for (int z = 0; z < ElementsAmount; z++)
			{
				if (z + ElementsAmount * (y + ElementsAmount * x) >= pow(ElementsAmount, 3)) continue;

				FGridCell& Cell = GetCell(x, y, z);
				if (Cell.OccupyingActor) {
					UFireSimulationComponent* FireComp = ActorToFireCompMap.FindRef(Cell.OccupyingActor);
					Cell.mass = FireComp->Mass / ActorCellsCount[Cell.OccupyingActor];
				}
			}
		}
	}


	// LOGS
	FString FilePath = FPaths::ProjectDir() / TEXT("GridLog.txt");
	FFileHelper::SaveStringToFile(LogText, *FilePath);
}

TArray<FGridCell*> AFireGridManager::GetBurningCells() {
	TArray<FGridCell*> BurningCells;
	for (int i = 0; i < ElementsAmount; i++) {
		for (int j = 0; j < ElementsAmount; j++) {
			for (int k = 0; k < ElementsAmount; k++) {
				if (k + ElementsAmount * (j + ElementsAmount * i) >= pow(ElementsAmount, 3)) continue;

				FGridCell& Cell = GetCell(i, j, k);
				if (Cell.Status == BURNING) {
					BurningCells.Add(&Cell);
				}
			}
		}
	}
	return BurningCells;
}


void AFireGridManager::CreateFireActor(FGridCell* Cell, UWorld* World)
{
	if (!SelectedParticleFire || !World)
	{
		UE_LOG(LogTemp, Warning, TEXT("VLAD! NO WORLD!"));
		return;
	}

	// Вычисляем локацию ячейки
	UBoxComponent* GridBoxComponent = GridActor->FindComponentByClass<UBoxComponent>();

	FVector GridSize = GridBoxComponent->GetScaledBoxExtent() * 2;
	FVector CellSize(GridSize.X / ElementsAmount, GridSize.Y / ElementsAmount, GridSize.Z / ElementsAmount);
	FVector GridOrigin = GridBoxComponent->GetComponentLocation() - GridSize / 2;

	FVector CellCenter = GridOrigin + FVector(Cell->x * CellSize.X, Cell->y * CellSize.Y, Cell->z * CellSize.Z) + CellSize / 2;

	FCollisionQueryParams QueryParams;
	QueryParams.bTraceComplex = true;
	QueryParams.AddIgnoredActor(GridActor); 

	TArray<FOverlapResult> Overlaps;
	FVector Extent(FireParticleSize, FireParticleSize, FireParticleSize);
	FCollisionShape CollisionShape = FCollisionShape::MakeBox(Extent);

	if (World->OverlapMultiByChannel(Overlaps, CellCenter, FQuat::Identity, ECC_GameTraceChannel1, CollisionShape))
	{
		for (const FOverlapResult& Result : Overlaps)
		{
			AActor* OverlappedActor = Result.GetActor();
			if (OverlappedActor)
			{
				UParticleSystemComponent* ParticleSystemComponent = OverlappedActor->FindComponentByClass<UParticleSystemComponent>();
				if (ParticleSystemComponent && ParticleSystemComponent->Template == SelectedParticleFire)
				{
					// Найден актор с нужной системой частиц, не создаем нового
					return;
				}
			}
		}
	}
	// Создаем актор огня
	FActorSpawnParameters SpawnParams;
	FRotator Rotation(0);
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	AActor* SpawnedActor = World->SpawnActor<AActor>(AActor::StaticClass(), CellCenter, Rotation, SpawnParams);

	if (SpawnedActor)
	{
		UBoxComponent* ActorBoxComponent = NewObject<UBoxComponent>(SpawnedActor);
		if (ActorBoxComponent)
		{
			ActorBoxComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
			ActorBoxComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
			ActorBoxComponent->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Overlap);
			ActorBoxComponent->InitBoxExtent(FVector(FireParticleSize, FireParticleSize, FireParticleSize)); // Можно настроить под себя
			ActorBoxComponent->SetWorldLocation(CellCenter);
			ActorBoxComponent->RegisterComponent();
			SpawnedActor->AddInstanceComponent(ActorBoxComponent);
		}
	}

	UParticleSystem* SelectedParticleSystem = Cast<UParticleSystem>(SelectedParticleFire);
	UParticleSystemComponent* ParticleSystemComponent = NewObject<UParticleSystemComponent>(SpawnedActor, UParticleSystemComponent::StaticClass());
	SpawnedActor->AddInstanceComponent(ParticleSystemComponent);
	ParticleSystemComponent->SetTemplate(SelectedParticleSystem);
	ParticleSystemComponent->RegisterComponent();
	ParticleSystemComponent->SetWorldLocation(CellCenter);
	ParticleSystemComponent->SetVisibility(true);
	ParticleSystemComponent->Activate();
	SpawnedActor->RegisterAllComponents();

	Cell->FireActor = SpawnedActor;
}


void AFireGridManager::RemoveBurntActor(FGridCell* Cell) {
	for (int i = 0; i < ElementsAmount; ++i) {
		for (int j = 0; j < ElementsAmount; ++j) {
			for (int k = 0; k < ElementsAmount; ++k) {
				if (GetCell(i, j, k).OccupyingActor == Cell->OccupyingActor && Cell->FireActor) {
					Cell->FireActor->Destroy();
					Cell->FireActor = nullptr;
				}
			}
		}
	}

    if (Cell->OccupyingActor) {
		Cell->OccupyingActor->SetActorHiddenInGame(true);
		Cell->OccupyingActor->SetActorEnableCollision(false);
		Cell->OccupyingActor->SetActorTickEnabled(false);
		Cell->OccupyingActor->MarkComponentsRenderStateDirty();
	}
}