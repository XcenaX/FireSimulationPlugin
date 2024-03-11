#include "BuildingGraph.h"
#include "Particles/ParticleSystemComponent.h"

URoomNode::URoomNode()
	: RoomID(-1), IsGasSource(false), CombustionCompletenessCoefficient(0.0f),
	HeatAbsorptionCoefficient(0.0f), StartTemperature(0.0f), InitialGasDensity(0.0f),
	Cp(0.0f), RoomVolume(0.0f), heat_of_combustion_(0.0f), linear_flame_speed_rate_(0.0f),
	specific_fuel_burn_rate_(0.0f), smoke_forming_ability_(0.0f)
{
}

void URoomNode::Initialize(int32 InRoomID = -1, bool InIsGasSource = false, float InCombustionCompletenessCoefficient = 0,
	float InHeatAbsorptionCoefficient = 0, float InStartTemperature = 0, float InInitialGasDensity = 0,
	float InCp = 0, float InRoomVolume = 0, float InHeatOfCombustion = 0, float InLinearFlameSpeedRate = 0,
	float InSpecificFuelBurnRate = 0, float InSmokeFormingAbility = 0, UWorld* InWorld = nullptr)
{
	World = InWorld;
	RoomID = InRoomID;
	IsGasSource = InIsGasSource;
	CombustionCompletenessCoefficient = InCombustionCompletenessCoefficient;
	HeatAbsorptionCoefficient = InHeatAbsorptionCoefficient;
	StartTemperature = InStartTemperature;
	InitialGasDensity = InInitialGasDensity;
	Cp = InCp;
	RoomVolume = InRoomVolume;
	heat_of_combustion_ = InHeatOfCombustion;
	linear_flame_speed_rate_ = InLinearFlameSpeedRate;
	specific_fuel_burn_rate_ = InSpecificFuelBurnRate;
	smoke_forming_ability_ = InSmokeFormingAbility;

	calculated_params_ = InitializeCalculatedParams();
}

void URoomNode::Initialize(int32 InRoomID = -1, bool InIsGasSource = false, float InCombustionCompletenessCoefficient = 0,
	float InHeatAbsorptionCoefficient = 0, float InStartTemperature = 0, float InInitialGasDensity = 0,
	float InCp = 0, float InRoomVolume = 0, float InHeatOfCombustion = 0, float InLinearFlameSpeedRate = 0,
	float InSpecificFuelBurnRate = 0, float InSmokeFormingAbility = 0)
{
	World = nullptr;
	RoomID = InRoomID;
	IsGasSource = InIsGasSource;
	CombustionCompletenessCoefficient = InCombustionCompletenessCoefficient;
	HeatAbsorptionCoefficient = InHeatAbsorptionCoefficient;
	StartTemperature = InStartTemperature;
	InitialGasDensity = InInitialGasDensity;
	Cp = InCp;
	RoomVolume = InRoomVolume;
	heat_of_combustion_ = InHeatOfCombustion;
	linear_flame_speed_rate_ = InLinearFlameSpeedRate;
	specific_fuel_burn_rate_ = InSpecificFuelBurnRate;
	smoke_forming_ability_ = InSmokeFormingAbility;

	calculated_params_ = InitializeCalculatedParams();
}


FCalculatedParameters URoomNode::GetCalculatedParameters() const
{
	return calculated_params_;
}

void URoomNode::UpdateFireDynamics(const FFireDynamicsParameters& NewParams)
{
	fire_dynamics_ = NewParams;
}

FFireDynamicsParameters URoomNode::GetFireDynamics() const
{
	return fire_dynamics_;
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

void UGraphEdge::Initialize(int32 InRoomStartID = -1, int32 InRoomEndID = -1, float InConnectionStrength = -1)
{
	RoomStartID = InRoomStartID;
	RoomEndID = InRoomEndID;
	ConnectionStrength = InConnectionStrength;
}

void URoomNode::SpawnFog(float visibility)
{
	if (!World) return;
	FVector RoomCenter = RoomMarker->RoomBounds->GetComponentLocation();
	FVector RoomExtent = RoomMarker->RoomBounds->GetScaledBoxExtent();

	float EmitterHeight = 20.0f; // Высота между эмиттерами
	float Offset = 30.0f;
	int32 NumEmittersZ = FMath::FloorToInt((RoomExtent.Z * 2) / (EmitterHeight + Offset)); // Расчет количества эмиттеров по Z
	int32 NumEmittersX = FMath::CeilToInt(RoomMarker->RoomBounds->GetScaledBoxExtent().X * 2 / 150);
	int32 NumEmittersY = FMath::CeilToInt(RoomMarker->RoomBounds->GetScaledBoxExtent().Y * 2 / 150);

	for (int32 x = 0; x < NumEmittersX; ++x)
	{
		for (int32 y = 0; y < NumEmittersY; ++y)
		{
			for (int32 z = 0; z < NumEmittersZ; ++z)
			{
				FVector EmitterLocation(
					RoomCenter.X - RoomExtent.X + (x * 150) + 75, // +75 чтобы центрировать в своей ячейке
					RoomCenter.Y - RoomExtent.Y + (y * 150) + 75,
					RoomExtent.Z - (z * (EmitterHeight + Offset)) + EmitterHeight / 2 // Центрирование по Z в своем слое
				);

				FActorSpawnParameters SpawnParams;
				FRotator Rotation(0);
				SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
				AActor* SpawnedActor = World->SpawnActor<AActor>(AActor::StaticClass(), EmitterLocation, Rotation, SpawnParams);

				UParticleSystemComponent* ParticleSystemComponent = NewObject<UParticleSystemComponent>(SpawnedActor, UParticleSystemComponent::StaticClass());
				UParticleSystem* ParticleSystemAsset = LoadObject<UParticleSystem>(nullptr, TEXT("/FireSimulation/Fog_PS"));

				SpawnedActor->AddInstanceComponent(ParticleSystemComponent);
				ParticleSystemComponent->SetTemplate(ParticleSystemAsset);
				ParticleSystemComponent->RegisterComponent(); // Регистрация компонента 
				ParticleSystemComponent->SetRelativeLocation(EmitterLocation);

				ParticleSystemComponent->SetVisibility(true);
				ParticleSystemComponent->Activate();
				SpawnedActor->RegisterAllComponents();

				UpdateFogVisibility(visibility);
				RoomMarker->FogEmitters.Add(ParticleSystemComponent);
			}
		}
	}
}

void URoomNode::UpdateFogVisibility(float Visibility)
{
	// Значения параметров (примеры, требуется настройка)
	float BaseExtinction = 0.1f;
	float k = 5.0f; // Коэффициент влияния видимости (надо эмпирический потестить это)

	Visibility = FMath::Max(Visibility, 1.0f); // Видимость не может быть меньше 1 метра (можно изменить если надо)

	float NewExtinction = BaseExtinction + k * (1 / Visibility);

	for (UParticleSystemComponent* Emitter : RoomMarker->FogEmitters)
	{
		if (Emitter)
		{
			Emitter->SetFloatParameter(FName("Extinction"), NewExtinction);
		}
	}
}

void URoomNode::RemoveFog()
{
	for (UParticleSystemComponent* Emitter : RoomMarker->FogEmitters)
	{
		if (Emitter)
		{
			Emitter->DestroyComponent();
		}
	}
}


void UBuildingGraph::PrepareGraphToWork()
{
	FindSourceRoomId();
	TopologicalSort();
}

void UBuildingGraph::AddRoom(const URoomNode* Room)
{
	if (Room)
	{
		if (!Rooms.Contains(Room->RoomID)) {
			Rooms.Add(Room->RoomID, const_cast<URoomNode*>(Room));
		}
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

	UGraphEdge* NewEdge = NewObject<UGraphEdge>();
	if (!NewEdge)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to create a new UGraphEdge instance."));
		return;
	}
	NewEdge->RoomStartID = StartRoomID;
	NewEdge->RoomEndID = EndRoomID;
	NewEdge->SetConnectionStrengthFromStatus(ConnectionStatus);

	FGraphEdgePtr NewEdgePtr;
	NewEdgePtr.Edge = NewEdge;

	OutgoingConnections.FindOrAdd(StartRoomID).Edges.Add(NewEdgePtr);
	IncomingConnections.FindOrAdd(EndRoomID).Edges.Add(NewEdgePtr);
}

const TMap<int32, URoomNode*>& UBuildingGraph::GetRooms() const
{
	return Rooms;
}

void UBuildingGraph::FindSourceRoomId()
{
	TArray<int32> FoundSourceRooms;
	for (const auto& RoomPair : Rooms)
	{
		if (RoomPair.Value->IsGasSource)
		{
			FoundSourceRooms.Add(RoomPair.Key);
		}
	}

	if (FoundSourceRooms.Num() > 1)
	{
		UE_LOG(LogTemp, Warning, TEXT("Multiple fire sources detected. There should be only one source of fire."));
		for (int32 RoomId : FoundSourceRooms)
		{
			UE_LOG(LogTemp, Warning, TEXT("Fire source found in room ID: %d"), RoomId);
		}
		SourceRoomID = -1;
	}
	else if (FoundSourceRooms.Num() == 1)
	{
		SourceRoomID = FoundSourceRooms[0];
		UE_LOG(LogTemp, Warning, TEXT("Fire source found in room ID: %d"), SourceRoomID);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("No fire sources detected. There should be only one source of fire."));
		SourceRoomID = -1;
	}
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

		for (const UGraphEdge* Connection : IncomingConnections[Room->RoomID].Edges)
		{
			int32 adjacentRoomId = Connection->RoomStartID;
			URoomNode* AdjacentRoom = Rooms[adjacentRoomId];
			FFireDynamicsParameters AdjacentRoomFireDynamicsParams = AdjacentRoom->GetFireDynamics();
			float ConnectionStrength = Connection->ConnectionStrength;

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

void UBuildingGraph::CalculateFireDynamicsForSecond(int32 Second, float TimeStep)
{
	if (SourceRoomID == -1)
	{
		UE_LOG(LogTemp, Error, TEXT("No source room (fire origin) was found in the graph."));
		return;
	}

	for (auto& Room : Rooms)
	{
		FFireDynamicsParameters CurrentParams = CalculateFireDynamicsForRoom(Room.Value, Second);
		Room.Value->UpdateFireDynamics(CurrentParams);
		
		UE_LOG(LogTemp, Warning, TEXT("Second: %d; ROOM %d : visibility: %f; volume: %f; other: %f, %f, %f, %f"), Second, Room.Value->RoomID, (double)CurrentParams.Visibility, (double)Room.Value->RoomVolume, (double)CurrentParams.BurnedMass, (double)CurrentParams.GasDensity, (double)CurrentParams.GasTemperature, (double)CurrentParams.SmokeExtinctionCoefficient);

		// Если в комнате есть дым надо проверить есть ли в ней Particle Sytem, если нет - создать, если да - обновить видимость
		if (CurrentParams.Visibility != 30.0) {
			if (Room.Value->RoomMarker->FogEmitters.Num() == 0) {
				UE_LOG(LogTemp, Warning, TEXT("SPAWN FOG"));
				Room.Value->SpawnFog(CurrentParams.Visibility);
			}
			else {
				UE_LOG(LogTemp, Warning, TEXT("UPDATE FOG"));
				Room.Value->UpdateFogVisibility(CurrentParams.Visibility);
			}
		}
	}
}

bool UBuildingGraph::TopologicalSort()
{
	TMap<int32, int32> InDegrees;
	TQueue<int32> ZeroInDegreeNodes;
	TArray<int32> SortedRoomIDs;

	for (auto& RoomPair : Rooms) {
		InDegrees.Add(RoomPair.Key, 0);
	}
	for (auto& ConnectionSet : OutgoingConnections) {
		for (UGraphEdge* Edge : ConnectionSet.Value.Edges) {
			InDegrees[Edge->RoomEndID]++;
		}
	}

	for (auto& DegreePair : InDegrees) {
		if (DegreePair.Value == 0) {
			ZeroInDegreeNodes.Enqueue(DegreePair.Key);
		}
	}

	while (!ZeroInDegreeNodes.IsEmpty()) {
		int32 CurrentNode;
		ZeroInDegreeNodes.Dequeue(CurrentNode);
		SortedRoomIDs.Add(CurrentNode);

		if (OutgoingConnections.Contains(CurrentNode)) {
			for (UGraphEdge* Edge : OutgoingConnections[CurrentNode].Edges) {
				InDegrees[Edge->RoomEndID]--;
				if (InDegrees[Edge->RoomEndID] == 0) {
					ZeroInDegreeNodes.Enqueue(Edge->RoomEndID);
				}
			}
		}
	}

	if (SortedRoomIDs.Num() != Rooms.Num()) {
		return false;
	}

	TMap<int32, URoomNode*> NewSortedRooms;
	for (int32 RoomID : SortedRoomIDs) {
		NewSortedRooms.Add(RoomID, Rooms[RoomID]);
	}
	Rooms = NewSortedRooms;

	return true;
}

bool UBuildingGraph::MergeToSourceRoom(int32 TargetRoomID)
{
	// ���������, ���������� �� �������
	if (!Rooms.Contains(SourceRoomID) || !Rooms.Contains(TargetRoomID))
	{
		UE_LOG(LogTemp, Warning, TEXT("One of the rooms does not exist."));
		return false;
	}

	// ���������, �� �������� �� �� ����� ������� ���� � �����
	if (SourceRoomID == TargetRoomID)
	{
		UE_LOG(LogTemp, Warning, TEXT("Attempting to merge the same room."));
		return false;
	}

	bool directConnectionExists = false;
	if (OutgoingConnections.Contains(SourceRoomID))
	{
		for (const UGraphEdge* Edge : OutgoingConnections[SourceRoomID].Edges)
		{
			if (Edge->RoomEndID == TargetRoomID)
			{
				directConnectionExists = true;
				break;
			}
		}
	}
	if (!directConnectionExists)
	{
		UE_LOG(LogTemp, Warning, TEXT("No direct connection from fire source to target room."));
		return false;
	}

	URoomNode* SourceRoom = Rooms[SourceRoomID];
	URoomNode* TargetRoom = Rooms[TargetRoomID];

	// ��������� �������, ��������� ������ � ������ ���������
	float TotalVolume = SourceRoom->RoomVolume + TargetRoom->RoomVolume;
	if (TotalVolume > 0)
	{
		// ��������� ��������� �������� �������
		SourceRoom->InitialGasDensity = (SourceRoom->InitialGasDensity * SourceRoom->RoomVolume + TargetRoom->InitialGasDensity * TargetRoom->RoomVolume) / TotalVolume;
		SourceRoom->StartTemperature = (SourceRoom->StartTemperature * SourceRoom->RoomVolume + TargetRoom->StartTemperature * TargetRoom->RoomVolume) / TotalVolume;
		// �������������� ��������� ����� ��������� �� ��������

		SourceRoom->RoomVolume = TotalVolume;
	}

	// ��������� �������� ���� � ������� ������� ������� �� �����
	SourceRoom->UpdateFireDynamics(TargetRoom->GetFireDynamics());
	Rooms.Remove(TargetRoomID);

	// ��������� ����� ����� �������
	UpdateGraphConnectionsAfterMergeToSourceRoom(TargetRoomID);

	UE_LOG(LogTemp, Log, TEXT("Rooms merged: SourceRoomID: %d, TargetRoomID: %d"), SourceRoomID, TargetRoomID);

	return true; // ���������, ��� ������� ��������� �������
}

struct FEdgeKey
{
	int32 StartID;
	int32 EndID;

	FEdgeKey(int32 InStartID, int32 InEndID) : StartID(InStartID), EndID(InEndID) {}

	bool operator==(const FEdgeKey& Other) const
	{
		return StartID == Other.StartID && EndID == Other.EndID;
	}

	friend uint32 GetTypeHash(const FEdgeKey& Key)
	{
		return HashCombine(::GetTypeHash(Key.StartID), ::GetTypeHash(Key.EndID));
	}
};

void UBuildingGraph::UpdateGraphConnectionsAfterMergeToSourceRoom(int32 TargetRoomID)
{
	if (OutgoingConnections.Contains(SourceRoomID)) {
		for (auto It = OutgoingConnections[SourceRoomID].Edges.CreateIterator(); It; ++It) {
			if ((*It).Edge->RoomEndID == TargetRoomID) {
				It.RemoveCurrent();
				break;
			}
		}
	}

	if (IncomingConnections.Contains(TargetRoomID)) {
		for (auto It = IncomingConnections[TargetRoomID].Edges.CreateIterator(); It; ++It) {
			if ((*It).Edge->RoomStartID == SourceRoomID) {
				It.RemoveCurrent();
				break;
			}
		}
	}

	TMap<FEdgeKey, TArray<float>> EdgeStrengths;

	if (OutgoingConnections.Contains(TargetRoomID)) {
		FGraphEdgeSet& TargetEdges = OutgoingConnections[TargetRoomID];
		for (UGraphEdge* Edge : TargetEdges.Edges) {
			UGraphEdge* NewEdge = DuplicateObject(Edge, this);
			NewEdge->RoomStartID = SourceRoomID;

			FEdgeKey Key(SourceRoomID, NewEdge->RoomEndID);
			EdgeStrengths.FindOrAdd(Key).Add(NewEdge->ConnectionStrength);

			FGraphEdgePtr NewEdgePtr;
			NewEdgePtr.Edge = NewEdge;

			OutgoingConnections[SourceRoomID].Edges.Add(NewEdgePtr);
			IncomingConnections[Edge->RoomEndID].Edges.Add(NewEdgePtr);

			if (IncomingConnections.Contains(Edge->RoomEndID)) {
				for (auto It = IncomingConnections[Edge->RoomEndID].Edges.CreateIterator(); It; ++It) {
					if ((*It).Edge->RoomStartID == TargetRoomID) {
						(*It).Edge->RoomStartID = SourceRoomID;
					}
				}
			}
		}
		OutgoingConnections.Remove(TargetRoomID);
	}

	if (IncomingConnections.Contains(TargetRoomID)) {
		FGraphEdgeSet& TargetIncomingEdges = IncomingConnections[TargetRoomID];
		for (UGraphEdge* Edge : TargetIncomingEdges.Edges) {
			UGraphEdge* NewEdge = DuplicateObject(Edge, this);
			NewEdge->RoomEndID = SourceRoomID;

			FEdgeKey Key(Edge->RoomStartID, SourceRoomID);
			EdgeStrengths.FindOrAdd(Key).Add(NewEdge->ConnectionStrength);

			if (OutgoingConnections.Contains(Edge->RoomStartID)) {
				FGraphEdgeSet& StartNodeOutgoing = OutgoingConnections[Edge->RoomStartID];
				FGraphEdgePtr EdgePtr;
				EdgePtr.Edge = Edge;
				StartNodeOutgoing.Edges.Remove(EdgePtr);
			}

			FGraphEdgePtr NewEdgePtr;
			NewEdgePtr.Edge = NewEdge;

			OutgoingConnections[Edge->RoomStartID].Edges.Add(NewEdgePtr);

			IncomingConnections[SourceRoomID].Edges.Add(NewEdgePtr);
		}
		IncomingConnections.Remove(TargetRoomID);
	}


	for (auto& Elem : EdgeStrengths)
	{
		FEdgeKey Key = Elem.Key;
		const TArray<float>& Strengths = Elem.Value;

		float AvgStrength = 0;
		for (float Strength : Strengths)
		{
			UE_LOG(LogTemp, Warning, TEXT("Test: Strength: %d"), Strength);
			AvgStrength += Strength;
		}
		AvgStrength /= Strengths.Num();

		UGraphEdge* NewEdge = NewObject<UGraphEdge>(this);
		NewEdge->RoomStartID = Key.StartID;
		NewEdge->RoomEndID = Key.EndID;
		NewEdge->ConnectionStrength = AvgStrength;

		FGraphEdgePtr NewEdgePtr;
		NewEdgePtr.Edge = NewEdge;

		OutgoingConnections.FindOrAdd(Key.StartID).Edges.Add(NewEdgePtr);
		IncomingConnections.FindOrAdd(Key.EndID).Edges.Add(NewEdgePtr);
	}
}

void UBuildingGraph::ClearAllRooms() {
	for (auto& RoomPair : Rooms)
	{
		URoomNode* Room = RoomPair.Value;
		if (Room)
		{
			Room->RemoveFog();
		}
	}
}
