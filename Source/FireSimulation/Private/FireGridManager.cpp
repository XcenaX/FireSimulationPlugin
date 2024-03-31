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
#include <MaterialDataManager.h>


UFireGridManager::UFireGridManager()
{
	// Инициализация переменных и состояний по умолчанию
}

void UFireGridManager::InitializeGrid(UWorld* NewWorld, AGridActor* NewGridActor, int32 NewCellSize, int32 NewThreads, int32 FireSize, UParticleSystem* FireParticle)
{
	Threads = NewThreads;
	FireParticleSize = FireSize;
	CellSize = NewCellSize;
	SelectedParticleFire = FireParticle;
	GridActor = NewGridActor;
	World = NewWorld;

	if (!World) {
		UE_LOG(LogTemp, Warning, TEXT("NO WORLD in InitializeGrid"));
	}
	if (!GridActor) {
		UE_LOG(LogTemp, Warning, TEXT("NO GRID ACTOR in InitializeGrid"));
	}

	// Получаем размеры границ сетки
	FVector GridSize = GridActor->GridBounds->GetScaledBoxExtent() * 2; // GetScaledBoxExtent возвращает половину размеров, умножаем на 2 для получения полных размеров

	// Вычисляем количество ячеек в каждом измерении
	int32 CellsX = FMath::CeilToInt(GridSize.X / CellSize);
	int32 CellsY = FMath::CeilToInt(GridSize.Y / CellSize);
	int32 CellsZ = FMath::CeilToInt(GridSize.Z / CellSize);

	ElementsAmountX = CellsX;
	ElementsAmountY = CellsY;
	ElementsAmountZ = CellsZ;

	Grid.Empty();
	for (int32 i = 0; i < CellsX; i++)
	{
		for (int32 j = 0; j < CellsY; j++)
		{
			for (int32 k = 0; k < CellsZ; k++) {
				FGridCell Cell;

				Cell.x = i;
				Cell.y = j;
				Cell.z = k;

				Grid.Add(Cell);
			}
		}
	}

	for (int32 i = 0; i < CellsX; i++)
	{
		for (int32 j = 0; j < CellsY; j++)
		{
			for (int32 k = 0; k < CellsZ; k++) {
				FGridCell& CurrentCell = GetCell(i, j, k);

				for (int32 dx = -1; dx <= 1; dx++) {
					for (int32 dy = -1; dy <= 1; dy++) {
						for (int32 dz = -1; dz <= 1; dz++) {
							if (dx == 0 && dy == 0 && dz == 0) continue;

							int32 newX = i + dx;
							int32 newY = j + dy;
							int32 newZ = k + dz;

							if (newX >= 0 && newX < CellsX &&
								newY >= 0 && newY < CellsY &&
								newZ >= 0 && newZ < CellsZ) {

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


void UFireGridManager::ClearGrid() {
	Grid.Empty();
	ActorToFireCompMap.Empty();
	ActorCellsCount.Empty();
}

FGridCell& UFireGridManager::GetCell(int32 x, int32 y, int32 z) {
	int32 index = z + ElementsAmountZ * (y + ElementsAmountY * x);
	return Grid[index];
}

void UFireGridManager::PopulateGridWithActors()
{
	if (!World || !GridActor || ElementsAmountX <= 0 || ElementsAmountY <= 0 || ElementsAmountZ <= 0) return;

	UBoxComponent* BoxComponent = GridActor->FindComponentByClass<UBoxComponent>();
	if (!BoxComponent) return;

    FVector GridSize = BoxComponent->GetScaledBoxExtent() * 2; // Получаем полные размеры 
    FVector CellSizeVector(GridSize.X / ElementsAmountX, GridSize.Y / ElementsAmountY, GridSize.Z / ElementsAmountZ);

	// Заполняем сетку акторами
	FVector GridOrigin = BoxComponent->GetComponentLocation() - GridSize / 2; // Начальная точка сетки	

	FCollisionQueryParams QueryParams;
	QueryParams.bReturnPhysicalMaterial = false;

	for (int32 x = 0; x < ElementsAmountX; x++)
	{
		for (int32 y = 0; y < ElementsAmountY; y++)
		{
			for (int32 z = 0; z < ElementsAmountZ; z++)
			{				
				FGridCell& Cell = GetCell(x, y, z);
				FVector CellCenter = GridOrigin + FVector(x * CellSizeVector.X, y * CellSizeVector.Y, z * CellSizeVector.Z) + CellSizeVector / 2;
				FCollisionShape Box = FCollisionShape::MakeBox(CellSizeVector / 2);
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
							if (Material && MaxLinearFlameSpeed < Material->LinearFlameSpeed || FireComp->IsBurning) {
								MaxLinearFlameSpeed = Material->LinearFlameSpeed;
								PickedActor = HitActor;
								PickedFireComp = FireComp;
							}
							if (FireComp->IsBurning) {
								break;
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
			}	
		}
	}

	for (int x = 0; x < ElementsAmountX; x++)
	{
		for (int y = 0; y < ElementsAmountY; y++)
		{
			for (int z = 0; z < ElementsAmountZ; z++)
			{
				FGridCell& Cell = GetCell(x, y, z);
				if (Cell.OccupyingActor) {
					UFireSimulationComponent* FireComp = ActorToFireCompMap.FindRef(Cell.OccupyingActor);
					Cell.mass = FireComp->Mass / ActorCellsCount[Cell.OccupyingActor];
				}
			}
		}
	}
}

TArray<FGridCell*> UFireGridManager::GetBurningCells() {
	TArray<FGridCell*> BurningCells;
	for (int i = 0; i < ElementsAmountX; i++) {
		for (int j = 0; j < ElementsAmountY; j++) {
			for (int k = 0; k < ElementsAmountZ; k++) {				
				FGridCell& Cell = GetCell(i, j, k);
				if (Cell.Status == BURNING) {
					BurningCells.Add(&Cell);
				}
			}
		}
	}
	return BurningCells;
}


void UFireGridManager::CreateFireActor(FGridCell* Cell)
{
	if (!SelectedParticleFire || !World)
	{
		UE_LOG(LogTemp, Warning, TEXT("VLAD! NO WORLD!"));
		return;
	}

	// Вычисляем локацию ячейки
	UBoxComponent* GridBoxComponent = GridActor->FindComponentByClass<UBoxComponent>();

	FVector GridSize = GridBoxComponent->GetScaledBoxExtent() * 2;
	FVector CellSizeVector(GridSize.X / ElementsAmountX, GridSize.Y / ElementsAmountY, GridSize.Z / ElementsAmountZ);
	FVector GridOrigin = GridBoxComponent->GetComponentLocation() - GridSize / 2;

	FVector CellCenter = GridOrigin + FVector(Cell->x * CellSizeVector.X, Cell->y * CellSizeVector.Y, Cell->z * CellSizeVector.Z) + CellSizeVector / 2;

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

void UFireGridManager::RemoveBurntActor(FGridCell* StartCell) {
	if (!StartCell || !StartCell->OccupyingActor) return;

	// Используем очередь для BFS
	TQueue<FGridCell*> Queue;
	Queue.Enqueue(StartCell);

	// Помечаем StartCell как обработанную, чтобы избежать повторного добавления в очередь
	TSet<AActor*> Processed;
	Processed.Add(StartCell->OccupyingActor);

	while (!Queue.IsEmpty()) {
		FGridCell* CurrentCell;
		Queue.Dequeue(CurrentCell);

		// Удаление FireActor и очистка ссылки, если они существуют
		if (CurrentCell->FireActor) {
			CurrentCell->FireActor->Destroy();
			CurrentCell->FireActor = nullptr;
		}

		// Перебор всех соседей текущей ячейки
		for (FGridCell* Neighbour : CurrentCell->Neighbours) {
			// Проверка, не обрабатывали ли мы уже эту ячейку или её актора
			if (Neighbour && Neighbour->OccupyingActor && !Processed.Contains(Neighbour->OccupyingActor)) {
				if (Neighbour->OccupyingActor->GetActorGuid() == CurrentCell->OccupyingActor->GetActorGuid()) {
					Queue.Enqueue(Neighbour); // Добавляем соседа в очередь для обработки
					Processed.Add(Neighbour->OccupyingActor); // Помечаем актора соседа как обработанного
				}
			}
		}
	}

	// Скрываем основного актора и отключаем его взаимодействие
	StartCell->OccupyingActor->SetActorHiddenInGame(true);
	StartCell->OccupyingActor->SetActorEnableCollision(false);
	StartCell->OccupyingActor->SetActorTickEnabled(false);
	StartCell->OccupyingActor->MarkComponentsRenderStateDirty();
}
