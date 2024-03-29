#include "SmokeManager.h"
#include "RoomMarker.h"
#include "DoorComponent.h"
#include "GridActor.h"
#include "EngineUtils.h"
#include <MaterialData.h>

USmokeManager::USmokeManager()
{
}

void USmokeManager::Initialize(UWorld* World) {
	UE_LOG(LogTemp, Warning, TEXT("INITIALIZING GRAPH"));

	graph = NewObject<UBuildingGraph>(this, "BuildingGraph");
	if (!graph)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to create UBuildingGraph."));
	}

	if (!World)
		UE_LOG(LogTemp, Warning, TEXT("NO WORLD"));

	if (!graph)
		UE_LOG(LogTemp, Warning, TEXT("NO GRAPH"));

	if (!graph || !World)
		return;

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

	int32 RoomCount = 1;
	for (ARoomMarker* Room : Rooms) {
		FMaterialData AverageMaterialData = Room->CalculateAverageMaterialData();
		Room->RoomID = RoomCount;

		TArray<AActor*> Actors = Room->GetActors();

		for (auto Actor : Actors) {
			ActorsLocation.Add(Actor->GetName(), Room);
		}

		bool IsGasSource = Room->IsGasSource(Actors);

		RoomsStatus.Add(Room->RoomID, IsGasSource);

		URoomNode* RoomNode = NewObject<URoomNode>(graph);

		RoomNode->Initialize(RoomCount, IsGasSource, Room->CombustionCompletenessCoefficient,
			Room->HeatAbsorptionCoefficient, Room->StartTemperature, Room->InitialGasDensity,
			Room->Cp, Room->GetRoomVolume(), AverageMaterialData.LowestHeatOfCombustion_kJ_per_kg, AverageMaterialData.LinearFlameSpeed,
			AverageMaterialData.BurningRate, AverageMaterialData.SmokeGeneration, GetWorld());

		UE_LOG(LogTemp, Warning, TEXT("ROOM %d : CombustionCompletenessCoefficient: %f; HeatAbsorptionCoefficient: %f; StartTemperature: %f, InitialGasDensity: %f;  Cp: %f ; Volume: %f ; LowestHeatOfCombustion_kJ_per_kg: %f ; LinearFlameSpeed: %f ; BurningRate: %f ; Smoke: %f"), RoomCount, (double)Room->CombustionCompletenessCoefficient, (double)Room->HeatAbsorptionCoefficient, (double)Room->StartTemperature, (double)Room->InitialGasDensity, (double)Room->Cp, (double)Room->GetRoomVolume(), (double)AverageMaterialData.LowestHeatOfCombustion_kJ_per_kg, (double)AverageMaterialData.LinearFlameSpeed, (double)AverageMaterialData.BurningRate, (double)AverageMaterialData.SmokeGeneration)

			RoomNode->RoomMarker = Room;

		graph->AddRoom(RoomNode);
		RoomCount++;
	}

	for (UDoorComponent* Door : Doors)
	{
		if (Door->ConnectedRoom1 && Door->ConnectedRoom2)
		{
			int32 StartRoomID = Door->ConnectedRoom1->RoomID;
			int32 EndRoomID = Door->ConnectedRoom2->RoomID;

			if (StartRoomID < 0 || EndRoomID < 0) continue;

			EConnectionStatus ConnectionStatus = Door->bIsOpen ? EConnectionStatus::DoorOpen : EConnectionStatus::DoorClosed;

			UE_LOG(LogTemp, Warning, TEXT("START_ROOM_ID: %d ; END_ROOM_ID: %d ; Status: %s"), StartRoomID, EndRoomID, *EnumToString(ConnectionStatus));

			graph->AddConnection(graph->GetRooms()[Door->ConnectedRoom1->RoomID], graph->GetRooms()[Door->ConnectedRoom2->RoomID], ConnectionStatus);
		}
	}
	graph->PrepareGraphToWork();

	UE_LOG(LogTemp, Warning, TEXT("GRAPH INITIALIZED"));

}

void USmokeManager::UpdateSmoke()
{
	graph->CalculateFireDynamicsForSecond(TotalTime, 1);
}

bool USmokeManager::GetRoomStatusForActor(FString Name)
{
	ARoomMarker** RoomMarkerPtr = ActorsLocation.Find(Name);
	if (RoomMarkerPtr == nullptr)
	{
		return false;
	}

	ARoomMarker* RoomMarker = *RoomMarkerPtr;
	const bool* StatusPtr = RoomsStatus.Find(RoomMarker->RoomID);
	if (StatusPtr == nullptr)
	{
		// Статус комнаты неизвестен
		return false;
	}

	return *StatusPtr;
}

void USmokeManager::SetRoomStatus(int32 RoomID, bool Status)
{
	bool* StatusPtr = RoomsStatus.Find(RoomID);
	if (StatusPtr != nullptr)
	{
		*StatusPtr = Status;
	}
	else
	{
		RoomsStatus.Add(RoomID, Status);
	}
}

int32 USmokeManager::GetRoomIdForActor(FString Name)
{
	ARoomMarker** RoomMarkerPtr = ActorsLocation.Find(Name);
	if (RoomMarkerPtr == nullptr)
	{
		return -1;
	}

	ARoomMarker* RoomMarker = *RoomMarkerPtr;
	return RoomMarker->RoomID;
}