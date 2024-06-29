#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include <RoomMarker.h>
#include "BuildingGraph.generated.h"

// Enumeration for door connection status
UENUM(BlueprintType)
enum class EConnectionStatus : uint8
{
	DoorClosed      UMETA(DisplayName = "Door Closed"),
	DoorOpen        UMETA(DisplayName = "Door Open"),
	NoDoor      UMETA(DisplayName = "No Door")
};

// Struct to hold calculated fire dynamics parameters
USTRUCT(BlueprintType)
struct FCalculatedParameters
{
public:
	GENERATED_BODY()

	// Various fire dynamics parameters
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Fire Dynamics")
	float A;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Fire Dynamics")
	float N;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Fire Dynamics")
	float GasReleasePerMeterBurn;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Fire Dynamics")
	float LimitGasDensity;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Fire Dynamics")
	float LimitGasTemperature;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Fire Dynamics")
	float LimitSmokeExtinctionCoefficient;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Fire Dynamics")
	float LimitVisibility;

	// Constructor initializing parameters to zero
	FCalculatedParameters()
		: A(0.f), N(0.f), GasReleasePerMeterBurn(0.f), LimitGasDensity(0.f),
		LimitGasTemperature(0.f), LimitSmokeExtinctionCoefficient(0.f), LimitVisibility(0.f)
	{
	}
};

// Struct to hold dynamic fire parameters
USTRUCT(BlueprintType)
struct FFireDynamicsParameters
{
public:
	GENERATED_BODY()

	// Various fire dynamics parameters
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Fire Dynamics")
	float BurnedMass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Fire Dynamics")
	float GasDensity;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Fire Dynamics")
	float GasTemperature;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Fire Dynamics")
	float SmokeExtinctionCoefficient;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Fire Dynamics")
	float Visibility;

	// Constructor initializing parameters to zero
	FFireDynamicsParameters()
		: BurnedMass(0.f), GasDensity(0.f), GasTemperature(0.f),
		SmokeExtinctionCoefficient(0.f), Visibility(0.f) {}
};

// Struct to store the state of a door
USTRUCT(BlueprintType)
struct FDoorStateImprint
{
	GENERATED_BODY()

	// ID of the room from which the door state is recorded
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Door")
	int32 FromRoomID;

	// Status of the door
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Door")
	EConnectionStatus Status;
};

// Class representing a room node in the building graph
UCLASS(BlueprintType)
class FIRESIMULATION_API URoomNode : public UObject
{
public:
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Room")
	int32 RoomID;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Room")
	bool IsGasSource;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Room")
	float CombustionCompletenessCoefficient;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Room")
	float HeatAbsorptionCoefficient;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Room")
	float StartTemperature;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Room")
	float InitialGasDensity;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Room")
	float Cp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Room")
	float RoomVolume;

	// Pointer to the room marker actors
	TArray<ARoomMarker*> RoomMarkers;

	// Pointer to the world
	UWorld* World;

	URoomNode();

	void Initialize(int32 InRoomID, bool InIsGasSource, float InCombustionCompletenessCoefficient,
		float InHeatAbsorptionCoefficient, float InStartTemperature, float InInitialGasDensity,
		float InCp, float InRoomVolume, float InHeatOfCombustion, float InLinearFlameSpeedRate,
		float InSpecificFuelBurnRate, float InSmokeFormingAbility, UWorld* InWorld);

	UFUNCTION(BlueprintCallable, Category = "Room")
	FCalculatedParameters GetCalculatedParameters() const;

	UFUNCTION(BlueprintCallable, Category = "Room")
	void UpdateFireDynamics(const FFireDynamicsParameters& NewParams);

	UFUNCTION(BlueprintCallable, Category = "Room")
	FFireDynamicsParameters GetFireDynamics() const;

	UFUNCTION(BlueprintCallable, Category = "Room")
	FFireDynamicsParameters GetFireDynamicsImprint() const;

	UFUNCTION(BlueprintCallable, Category = "Room")
	int32 GetTimeImprint() const;

	UFUNCTION(BlueprintCallable, Category = "Room")
	FDoorStateImprint GetDoorStateImprint() const;

	UFUNCTION(BlueprintCallable, Category = "Room")
	FCalculatedParameters InitializeCalculatedParams();

	// Spawn fog in the room with a given visibility
	UFUNCTION(BlueprintCallable, Category = "Room")
	void SpawnFog(float visibility);

	UFUNCTION(BlueprintCallable, Category = "Room")
	void UpdateFogVisibility(float visibility);

	UFUNCTION(BlueprintCallable, Category = "Room")
	void RemoveFog();

	// Make an imprint of the room state
	UFUNCTION(BlueprintCallable, Category = "Room")
	void MakeImprint(int32 Time, int32 ChangedDoorRoomID, EConnectionStatus NewDoorStatus);

	float heat_of_combustion_;
	float linear_flame_speed_rate_;
	float specific_fuel_burn_rate_;
	float smoke_forming_ability_;
	FCalculatedParameters calculated_params_;
	FFireDynamicsParameters fire_dynamics_;
protected:
	int32 time_imprint_;
	FFireDynamicsParameters fire_dynamics_imprint_;
	FDoorStateImprint door_state_imprint_;
};

// Class representing a graph edge in the building graph
UCLASS(BlueprintType)
class UGraphEdge : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GraphEdge")
	int32 RoomStartID;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GraphEdge")
	int32 RoomEndID;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GraphEdge")
	float ConnectionStrength;

	UGraphEdge() : RoomStartID(-1), RoomEndID(-1), ConnectionStrength(-1) {}

	void Initialize(int32 InRoomStartID, int32 InRoomEndID, float InConnectionStrength);

	// Set connection strength based on door status
	UFUNCTION(BlueprintCallable, Category = "GraphEdge")
	float SetConnectionStrengthFromStatus(EConnectionStatus ConnectionStatus)
	{
		switch (ConnectionStatus)
		{
		case EConnectionStatus::DoorClosed:
			ConnectionStrength = 0;
			return 0;
		case EConnectionStatus::DoorOpen:
			ConnectionStrength = 0.63f;
			return 0.63f;
		case EConnectionStatus::NoDoor:
			ConnectionStrength = 1;
			return 1;
		default:
			return 0;
		}
	}

	// Static function to get connection strength from door status
	UFUNCTION(BlueprintCallable, Category = "GraphEdge")
	static float GetConnectionStrengthFromStatus(EConnectionStatus ConnectionStatus)
	{
		switch (ConnectionStatus)
		{
		case EConnectionStatus::DoorClosed:
			return 0;
		case EConnectionStatus::DoorOpen:
			return 0.63f;
		case EConnectionStatus::NoDoor:
			return 1;
		default:
			return 0;
		}
	}
};

// Struct representing a pointer to a graph edge
USTRUCT(BlueprintType)
struct FGraphEdgePtr
{
	GENERATED_BODY()

	UGraphEdge* Edge;

	// Operator overloading to allow usage of UGraphEdge* directly
	operator UGraphEdge* () const { return Edge; }
};

// Function to get hash of a graph edge
FORCEINLINE uint32 GetTypeHash(const UGraphEdge& Edge)
{
	return HashCombine(::GetTypeHash(Edge.RoomStartID), ::GetTypeHash(Edge.RoomEndID));
}

// Overload equality operator for graph edges
FORCEINLINE bool operator==(const UGraphEdge& A, const UGraphEdge& B)
{
	return A.RoomStartID == B.RoomStartID && A.RoomEndID == B.RoomEndID;
}

// Overload equality operator for graph edge pointers
FORCEINLINE bool operator==(const FGraphEdgePtr& A, const FGraphEdgePtr& B)
{
	return *A.Edge == *B.Edge;
}

// Function to get hash of a graph edge pointer
FORCEINLINE uint32 GetTypeHash(const FGraphEdgePtr& A)
{
	return ::GetTypeHash(*A.Edge);
}

// Struct representing a set of graph edges
USTRUCT(BlueprintType)
struct FGraphEdgeSet
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Building Graph")
	TSet<FGraphEdgePtr> Edges;
};

// Class representing the building graph
UCLASS(BlueprintType)
class FIRESIMULATION_API UBuildingGraph : public UObject
{
public:
	GENERATED_BODY()

	// Prepare the graph for use
	UFUNCTION(BlueprintCallable, Category = "Building Graph")
	void PrepareGraphToWork();

	UFUNCTION(BlueprintCallable, Category = "Building Graph")
	void AddRoom(URoomNode* Room);

	UFUNCTION(BlueprintCallable, Category = "Building Graph")
	void AddConnection(const URoomNode* StartRoom, const URoomNode* EndRoom, EConnectionStatus ConnectionStatus);

	UFUNCTION(BlueprintCallable, Category = "Building Graph")
	const TMap<int32, URoomNode*>& GetRooms() const;

	UFUNCTION(BlueprintCallable, Category = "Building Graph")
	const TMap<int32, FGraphEdgeSet>& GetOutgoingConnections() const;

	UFUNCTION(BlueprintCallable, Category = "Building Graph")
	const TMap<int32, FGraphEdgeSet>& GetIncomingConnections() const;

	// Calculate fire dynamics for a given time
	UFUNCTION(BlueprintCallable, Category = "Building Graph")
	void CalculateFireDynamicsForSecond(int32 TimeInSeconds, float TimeStep = 1.0f);

	UFUNCTION(BlueprintCallable, Category = "Building Graph")
	bool MergeToSourceRoom(int32 TargetRoomID);

	// Merge a room to the source room
	UFUNCTION(BlueprintCallable, Category = "Building Graph")
	void ClearGraph();

	bool CorrectlySetuped = false;

protected:
	// Map of room IDs to room nodes
	UPROPERTY(VisibleAnywhere, Category = "Building Graph")
	TMap<int32, URoomNode*> Rooms;

	// Map of room IDs to outgoing connections
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Building Graph")
	TMap<int32, FGraphEdgeSet> OutgoingConnections;

	// Map of room IDs to incoming connections
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Building Graph")
	TMap<int32, FGraphEdgeSet> IncomingConnections;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Building Graph")
	int32 SourceRoomID;

	UFUNCTION(BlueprintCallable, Category = "Building Graph")
	void FindSourceRoomId();

	// Calculate fire dynamics for a room at a given time
	UFUNCTION(BlueprintCallable, Category = "Building Graph")
	FFireDynamicsParameters CalculateFireDynamicsForRoom(URoomNode* Room, float CurrentTime, bool IsImprint);

	// Perform topological sort on the graph
	UFUNCTION(BlueprintCallable, Category = "Building Graph")
	bool TopologicalSort();

	// Update graph connections after merging a room to the source room
	UFUNCTION(BlueprintCallable, Category = "Building Graph")
	void UpdateGraphConnectionsAfterMergeToSourceRoom(int32 TargetRoomID);

};