#include "FogManagerActor.h"
#include "RoomMarker.h"
#include "DoorComponent.h"
#include "BuildingGraph.h"
#include "GridActor.h"
#include "EngineUtils.h"
#include <MaterialData.h>

AFogManagerActor* AFogManagerActor::Instance = nullptr;

AFogManagerActor* AFogManagerActor::GetInstance()
{
	if (!Instance)
	{
		Instance = NewObject<AFogManagerActor>();
		Instance->AddToRoot(); // Предотвратить уничтожение сборщиком мусора
	}
	return Instance;
}

AFogManagerActor::AFogManagerActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

	// Создаем подобъект UBuildingGraph с использованием ObjectInitializer.CreateDefaultSubobject
	graph = ObjectInitializer.CreateDefaultSubobject<UBuildingGraph>(this, TEXT("BuildingGraph"));
	if (!graph)
	{
		// Обработка ошибки, если объект не был создан
		UE_LOG(LogTemp, Error, TEXT("Failed to create UBuildingGraph subobject."));
	}
}

void AFogManagerActor::BeginPlay()
{
	UE_LOG(LogTemp, Warning, TEXT("INITIALIZING GRAPH"));

	InitializeGraph(GetWorld());

	Super::BeginPlay();

	FEditorDelegates::EndPIE.AddUObject(this, &AFogManagerActor::OnEndPIE);
}

void AFogManagerActor::InitializeGraph(UWorld* World)
{
	if(!World)
		UE_LOG(LogTemp, Warning, TEXT("NO WORLD"));

	if(!graph)
		UE_LOG(LogTemp, Warning, TEXT("NO GRAPH"));

	if (!graph || !World)
		return;

	TArray<ARoomMarker*> Rooms;
	TArray<UDoorComponent*> Doors;

	for (TActorIterator<ARoomMarker> It(World); It; ++It)
	{
		ARoomMarker* Room = *It;
		Rooms.Add(Room);
	}
	for (TObjectIterator<UDoorComponent> It; It; ++It)
	{
		UDoorComponent* Door = *It;
		Doors.Add(Door);
	}

	for (ARoomMarker* Room : Rooms) {
		FMaterialData AverageMaterialData = Room->CalculateAverageMaterialData();

		URoomNode* RoomNode = NewObject<URoomNode>();

		RoomNode->Initialize(Room->RoomID, Room->IsGasSource(), Room->CombustionCompletenessCoefficient,
			Room->HeatAbsorptionCoefficient, Room->StartTemperature, Room->InitialGasDensity,
			Room->Cp, Room->GetRoomVolume(), AverageMaterialData.LowestHeatOfCombustion_kJ_per_kg, AverageMaterialData.LinearFlameSpeed,
			AverageMaterialData.BurningRate, AverageMaterialData.SmokeGeneration);

		RoomNode->RoomMarker = Room;

		graph->AddRoom(RoomNode);
	}

	for (UDoorComponent* Door : Doors)
	{
		if (Door->ConnectedRoom1 && Door->ConnectedRoom2)
		{
			int32 StartRoomID = Door->ConnectedRoom1->RoomID;
			int32 EndRoomID = Door->ConnectedRoom2->RoomID;

			EConnectionStatus ConnectionStatus = Door->bIsOpen ? EConnectionStatus::DoorOpen : EConnectionStatus::DoorClosed;

			graph->AddConnection(graph->GetRooms()[Door->ConnectedRoom1->RoomID], graph->GetRooms()[Door->ConnectedRoom2->RoomID], ConnectionStatus);
		}
	}
	graph->PrepareGraphToWork();

	UE_LOG(LogTemp, Warning, TEXT("GRAPH INITIALIZED"));

}

// После завершения игры в редакторе возвращаем все сгоревшие акторы на место и тушим пожар
void AFogManagerActor::OnEndPIE(const bool bIsSimulating)
{
	UE_LOG(LogTemp, Warning, TEXT("GAME ENDED"));
	RestoreScene();
}


void AFogManagerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Суммируем прошедшее время
	TimeAccumulator += DeltaTime;

	// Проверяем, прошла ли секунда
	if (TimeAccumulator >= 1.0f)
	{
		TotalTime += 1;
		UpdateFog();
		TimeAccumulator -= 1.0f;
	}
}


void AFogManagerActor::UpdateFog()
{
	graph->CalculateFireDynamicsForSecond(TotalTime);	
}


void AFogManagerActor::RestoreScene() { // Возвращает сцену к прежнему виду после завершения игры
	graph->ClearAllRooms();
}