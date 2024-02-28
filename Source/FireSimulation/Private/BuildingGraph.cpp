#include "BuildingGraph.h"

URoomNode::URoomNode()
	: RoomID(-1), IsGasSource(false), CombustionCompletenessCoefficient(0.0f),
	HeatAbsorptionCoefficient(0.0f), StartTemperature(0.0f), InitialGasDensity(0.0f),
	Cp(0.0f), RoomVolume(0.0f), heat_of_combustion_(0.0f), linear_flame_speed_rate_(0.0f),
	specific_fuel_burn_rate_(0.0f), smoke_forming_ability_(0.0f)
{
	calculated_params_ = InitializeCalculatedParams();
}

FCalculatedParameters URoomNode::GetCalculatedParameters() const
{
	return calculated_params_;
}

void URoomNode::AddToFireDynamicsHistory(const FFireDynamicsParameters& NewParams)
{
	fire_dynamics_history_.Add(NewParams);
}

TArray<FFireDynamicsParameters> URoomNode::GetFireDynamicsHistory() const
{
	return fire_dynamics_history_;
}

FCalculatedParameters URoomNode::InitializeCalculatedParams()
{
	FCalculatedParameters Params;
	Params.A = 1.05 * specific_fuel_burn_rate_ * FMath::Pow(linear_flame_speed_rate_, 2);
	Params.N = 3;
	Params.GasReleasePerMeterBurn = (CombustionCompletenessCoefficient * heat_of_combustion_ * (1 - HeatAbsorptionCoefficient)) / (StartTemperature * InitialGasDensity * Cp);
	Params.LimitGasDensity = 1 / Params.GasReleasePerMeterBurn;
	Params.LimitGasTemperature = StartTemperature * InitialGasDensity / Params.LimitGasDensity;
	Params.LimitSmokeExtinctionCoefficient = smoke_forming_ability_ / Params.GasReleasePerMeterBurn;
	Params.LimitVisibility = 2.38;

	return Params;
}

void UBuildingGraph::PrepareGraphToWork()
{
	FindSourceRoomId();
	TopologicalSort();
}

void UBuildingGraph::AddRoom(const URoomNode* Room)
{
	if (Room != nullptr && !Rooms.Contains(Room->RoomID))
	{
		Rooms.Add(Room->RoomID, const_cast<URoomNode*>(Room));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Room already exists or Room is nullptr."));
	}
}

void UBuildingGraph::AddConnection(const URoomNode* StartRoom, const URoomNode* EndRoom, EConnectionStatus ConnectionStatus)
{
	if (StartRoom == nullptr || EndRoom == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("AddConnection: One or both room pointers are null."));
		return;
	}

	int32 StartRoomID = StartRoom->RoomID;
	int32 EndRoomID = EndRoom->RoomID;

	if (!Rooms.Contains(StartRoomID) || !Rooms.Contains(EndRoomID))
	{
		UE_LOG(LogTemp, Warning, TEXT("AddConnection: One or both rooms do not exist in the graph."));
		return;
	}

	FGraphEdge NewEdge;
	NewEdge.RoomStartID = StartRoomID;
	NewEdge.RoomEndID = EndRoomID;
	NewEdge.ConnectionStatus = ConnectionStatus;

	OutgoingConnections.FindOrAdd(StartRoomID).Edges.Add(NewEdge);
	IncomingConnections.FindOrAdd(EndRoomID).Edges.Add(NewEdge);
}

const TMap<int32, URoomNode*>& UBuildingGraph::GetRooms() const
{
	return Rooms;
}

int32 UBuildingGraph::FindSourceRoomId()
{
	for (const auto& RoomPair : Rooms)
	{
		if (RoomPair.Value->IsGasSource)
		{
			SourceRoomID = RoomPair.Key;
			return RoomPair.Key;
		}
	}
	return -1;
}

FFireDynamicsParameters UBuildingGraph::CalculateFireDynamicsForRoom(URoomNode* Room, float CurrentTime)
{
	if (!Room)
	{
		UE_LOG(LogTemp, Warning, TEXT("Room is nullptr, cannot calculate fire dynamics."));
		return FFireDynamicsParameters();
	}
	FCalculatedParameters CalcParams = Room->GetCalculatedParameters();
	FFireDynamicsParameters FireDynamicsParams;

	bool bHasConnections = IncomingConnections.Contains(Room->RoomID) && IncomingConnections[Room->RoomID].Edges.Num() > 0;

	if (!bHasConnections)
	{
		FireDynamicsParams.BurnedMass = CalcParams.A * FMath::Pow(CurrentTime, CalcParams.N);
		FireDynamicsParams.GasDensity = CalcParams.LimitGasDensity + (Room->InitialGasDensity - CalcParams.LimitGasDensity) * FMath::Exp(-CalcParams.GasReleasePerMeterBurn * FireDynamicsParams.BurnedMass / Room->RoomVolume);
		FireDynamicsParams.GasTemperature = Room->StartTemperature * Room->InitialGasDensity / FireDynamicsParams.GasDensity;
		FireDynamicsParams.SmokeExtinctionCoefficient = CalcParams.LimitSmokeExtinctionCoefficient + (0 - CalcParams.LimitSmokeExtinctionCoefficient) * FMath::Exp(-CalcParams.GasReleasePerMeterBurn * FireDynamicsParams.BurnedMass / Room->RoomVolume);
		FireDynamicsParams.Visibility = FMath::Min(30.0f, CalcParams.LimitVisibility / FireDynamicsParams.SmokeExtinctionCoefficient);
	}
	else
	{
		int32 Count = 0;
		FireDynamicsParams.BurnedMass = 0;
		FireDynamicsParams.GasDensity = 0;
		FireDynamicsParams.GasTemperature = 0;
		FireDynamicsParams.SmokeExtinctionCoefficient = 0;
		FireDynamicsParams.Visibility = 0;

		for (const auto& Connection : IncomingConnections[Room->RoomID].Edges)
		{
			int32 adjacentRoomId = Connection.RoomStartID;
			URoomNode* AdjacentRoom = Rooms[adjacentRoomId];
			FFireDynamicsParameters AdjacentRoomFireDynamicsParams = AdjacentRoom->GetFireDynamicsHistory().Last();
			float ConnectionStrength = Connection.GetConnectionStrength();

			Count++;
			FireDynamicsParams.BurnedMass += AdjacentRoomFireDynamicsParams.BurnedMass;
			FireDynamicsParams.GasDensity += AdjacentRoomFireDynamicsParams.GasDensity;
			FireDynamicsParams.GasTemperature += AdjacentRoomFireDynamicsParams.GasTemperature;
			FireDynamicsParams.SmokeExtinctionCoefficient += AdjacentRoomFireDynamicsParams.SmokeExtinctionCoefficient;
			FireDynamicsParams.Visibility += FMath::Min(30.0f, CalcParams.LimitVisibility / FireDynamicsParams.SmokeExtinctionCoefficient);
		}

		if (Count > 0)
		{
			FireDynamicsParams.BurnedMass /= Count;
			FireDynamicsParams.GasDensity /= Count;
			FireDynamicsParams.GasTemperature /= Count;
			FireDynamicsParams.SmokeExtinctionCoefficient /= Count;
			FireDynamicsParams.Visibility /= Count;
		}
	}

	return FireDynamicsParams;
}

void UBuildingGraph::CalculateFireDynamicsForSecond(float Second, float TimeStep)
{
	if (SourceRoomID == -1)
	{
		UE_LOG(LogTemp, Error, TEXT("No source room (fire origin) was found in the graph."));
		return;
	}

	for (auto& Room : Rooms)
	{
		FFireDynamicsParameters CurrentParams = CalculateFireDynamicsForRoom(Room.Value, Second);
		Room.Value->AddToFireDynamicsHistory(CurrentParams);
	}
}

void UBuildingGraph::TopologicalSortUtil(int32 RoomID, TMap<int32, bool>& Visited, TArray<int32>& Stack)
{
	Visited[RoomID] = true;

	if (OutgoingConnections.Contains(RoomID))
	{
		for (auto& Edge : OutgoingConnections[RoomID].Edges)
		{
			int32 NextRoomID = Edge.RoomEndID;
			if (!Visited[NextRoomID])
			{
				TopologicalSortUtil(NextRoomID, Visited, Stack);
			}
		}
	}

	Stack.Push(RoomID);
}

void UBuildingGraph::TopologicalSort()
{
	TMap<int32, bool> Visited;
	TArray<int32> Stack;
	TArray<int32> SortedRoomIDs;

	for (auto& RoomPair : Rooms)
	{
		Visited.Add(RoomPair.Key, false);
	}

	for (auto& RoomPair : Rooms)
	{
		if (!Visited[RoomPair.Key])
		{
			TopologicalSortUtil(RoomPair.Key, Visited, Stack);
		}
	}

	while (Stack.Num() > 0)
	{
		SortedRoomIDs.Push(Stack.Pop());
	}

	TMap<int32, URoomNode*> NewSortedRooms;
	for (int32 RoomID : SortedRoomIDs)
	{
		NewSortedRooms.Add(RoomID, Rooms[RoomID]);
	}
	Rooms = NewSortedRooms;
}

void UBuildingGraph::MergeToSourceRoom(int32 TargetRoomID)
{
	if (!Rooms.Contains(SourceRoomID) || !Rooms.Contains(TargetRoomID))
	{
		UE_LOG(LogTemp, Warning, TEXT("One of the rooms does not exist or the same room."));
		return;
	}

	if (SourceRoomID == TargetRoomID)
	{
		UE_LOG(LogTemp, Warning, TEXT("Attempting to merge the same room."));
		return;
	}

	URoomNode* SourceRoom = Rooms[SourceRoomID];
	URoomNode* TargetRoom = Rooms[TargetRoomID];

	float TotalVolume = SourceRoom->RoomVolume + TargetRoom->RoomVolume;
	if (TotalVolume > 0)
	{
		SourceRoom->InitialGasDensity = (SourceRoom->InitialGasDensity * SourceRoom->RoomVolume + TargetRoom->InitialGasDensity * TargetRoom->RoomVolume) / TotalVolume;
		SourceRoom->StartTemperature = (SourceRoom->StartTemperature * SourceRoom->RoomVolume + TargetRoom->StartTemperature * TargetRoom->RoomVolume) / TotalVolume;
		SourceRoom->CombustionCompletenessCoefficient = (SourceRoom->CombustionCompletenessCoefficient * SourceRoom->RoomVolume + TargetRoom->CombustionCompletenessCoefficient * TargetRoom->RoomVolume) / TotalVolume;
		SourceRoom->HeatAbsorptionCoefficient = (SourceRoom->HeatAbsorptionCoefficient * SourceRoom->RoomVolume + TargetRoom->HeatAbsorptionCoefficient * TargetRoom->RoomVolume) / TotalVolume;
		SourceRoom->Cp = (SourceRoom->Cp * SourceRoom->RoomVolume + TargetRoom->Cp * TargetRoom->RoomVolume) / TotalVolume;

		SourceRoom->RoomVolume = TotalVolume;
	}

	for (const FFireDynamicsParameters& FireParam : TargetRoom->GetFireDynamicsHistory())
	{
		SourceRoom->AddToFireDynamicsHistory(FireParam);
	}

	Rooms.Remove(TargetRoomID);

	UpdateGraphConnectionsAfterMergeToSourceRoom(TargetRoomID);

	UE_LOG(LogTemp, Log, TEXT("Rooms merged: SourceRoomID: %d, TargetRoomID: %d"), SourceRoomID, TargetRoomID);
}

void UBuildingGraph::UpdateGraphConnectionsAfterMergeToSourceRoom(int32 TargetRoomID)
{
	if (OutgoingConnections.Contains(TargetRoomID))
	{
		for (auto& Edge : OutgoingConnections[TargetRoomID].Edges)
		{
			if (Edge.RoomEndID != SourceRoomID)
			{
				AddConnection(Rooms[SourceRoomID], Rooms[Edge.RoomEndID], Edge.ConnectionStatus);
			}
		}
		OutgoingConnections.Remove(TargetRoomID);
	}

	for (auto& Pair : IncomingConnections)
	{
		TArray<FGraphEdge>& Edges = Pair.Value.Edges;
		for (int32 i = Edges.Num() - 1; i >= 0; --i)
		{
			if (Edges[i].RoomEndID == TargetRoomID)
			{
				if (Edges[i].RoomStartID == SourceRoomID)
				{
					Edges.RemoveAt(i);
				}
				else
				{
					Edges[i].RoomEndID = SourceRoomID;
				}
			}
		}
	}

	for (auto& Pair : OutgoingConnections)
	{
		TArray<FGraphEdge>& Edges = Pair.Value.Edges;
		for (int32 i = Edges.Num() - 1; i >= 0; --i)
		{
			if (Edges[i].RoomStartID == TargetRoomID)
			{
				Edges[i].RoomStartID = SourceRoomID;
			}
		}
	}

	IncomingConnections.Remove(TargetRoomID);
}

