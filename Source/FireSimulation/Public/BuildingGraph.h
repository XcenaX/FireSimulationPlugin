#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include <RoomMarker.h>
#include "BuildingGraph.generated.h"

UENUM(BlueprintType)
enum class EConnectionStatus : uint8
{
    DoorClosed      UMETA(DisplayName = "Door Closed"),
    DoorOpen        UMETA(DisplayName = "Door Open"),
    NoDoor      UMETA(DisplayName = "No Door")
};

USTRUCT(BlueprintType)
struct FCalculatedParameters
{
public:
    GENERATED_BODY()

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Fire Dynamics")
    float A; // пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Fire Dynamics")
    float N; // пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ.

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Fire Dynamics")
    float GasReleasePerMeterBurn; // пїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅ, пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ.

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Fire Dynamics")
    float LimitGasDensity; // пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ.

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Fire Dynamics")
    float LimitGasTemperature; // пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ.

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Fire Dynamics")
    float LimitSmokeExtinctionCoefficient; // пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅ.

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Fire Dynamics")
    float LimitVisibility; // пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ.

    FCalculatedParameters()
        : A(0.f), N(0.f), GasReleasePerMeterBurn(0.f), LimitGasDensity(0.f),
        LimitGasTemperature(0.f), LimitSmokeExtinctionCoefficient(0.f), LimitVisibility(0.f)
    {
    }
};

USTRUCT(BlueprintType)
struct FFireDynamicsParameters
{
public:
    GENERATED_BODY()

    // пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Fire Dynamics")
    float BurnedMass;

    // пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ пїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Fire Dynamics")
    float GasDensity;

    // пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ пїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Fire Dynamics")
    float GasTemperature;

    // пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅ
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Fire Dynamics")
    float SmokeExtinctionCoefficient;

    // пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Fire Dynamics")
    float Visibility;

    // пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ
    FFireDynamicsParameters()
        : BurnedMass(0.f), GasDensity(0.f), GasTemperature(0.f),
        SmokeExtinctionCoefficient(0.f), Visibility(0.f) {}
};

UCLASS(BlueprintType)
class FIRESIMULATION_API URoomNode : public UObject
{
public: // пїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅ пїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ (RoomMarker)
    GENERATED_BODY()

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Room")
    int32 RoomID;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Room")
    bool IsGasSource;                                                   // пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Room")
    float CombustionCompletenessCoefficient;                            // пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Room")
    float HeatAbsorptionCoefficient;                                    // пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Room")
    float StartTemperature;                                             // пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Room")
    float InitialGasDensity;                                            // пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ пїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Room")
    float Cp;                                                           // пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Room")
    float RoomVolume;                                                   // пїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ

    ARoomMarker* RoomMarker;

    URoomNode();

    UFUNCTION(BlueprintCallable, Category = "Room")
    void Initialize(int32 InRoomID, bool InIsGasSource, float InCombustionCompletenessCoefficient,
        float InHeatAbsorptionCoefficient, float InStartTemperature, float InInitialGasDensity,
        float InCp, float InRoomVolume, float InHeatOfCombustion, float InLinearFlameSpeedRate,
        float InSpecificFuelBurnRate, float InSmokeFormingAbility);

    UFUNCTION(BlueprintCallable, Category = "Room")
    FCalculatedParameters GetCalculatedParameters() const;

    UFUNCTION(BlueprintCallable, Category = "Room")
    void UpdateFireDynamics(const FFireDynamicsParameters& NewParams);

    UFUNCTION(BlueprintCallable, Category = "Room")
    FFireDynamicsParameters GetFireDynamics() const;

    UFUNCTION(BlueprintCallable, Category = "Room")
    FCalculatedParameters InitializeCalculatedParams();

    // Спавнит в комнате туман с заданной начальной видимостью в метрах
    UFUNCTION(BlueprintCallable, Category = "Room")
    void SpawnFog(float visibility);

    // Обновляет видимость в метрах для тумана в комнате
    UFUNCTION(BlueprintCallable, Category = "Room")
    void UpdateFogVisibility(float visibility);

    // Удаляет весь дым
    UFUNCTION(BlueprintCallable, Category = "Room")
    void RemoveFog();

protected:
    float heat_of_combustion_;                               // пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ.
    float linear_flame_speed_rate_;                          // пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ.
    float specific_fuel_burn_rate_;                          // пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ.
    float smoke_forming_ability_;
    FCalculatedParameters calculated_params_;                // пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ, пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ.
    FFireDynamicsParameters fire_dynamics_;          // пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ.
};

UCLASS(BlueprintType)
class UGraphEdge : public UObject
{
    GENERATED_BODY()

public: // пїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅ пїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ (DoorComponent)
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="GraphEdge")
    int32 RoomStartID;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="GraphEdge")
    int32 RoomEndID;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GraphEdge")
    float ConnectionStrength;

    UGraphEdge() : RoomStartID(-1), RoomEndID(-1), ConnectionStrength(-1) {}

    void Initialize(int32 InRoomStartID, int32 InRoomEndID, float InConnectionStrength);

    UFUNCTION(BlueprintCallable, Category = "GraphEdge")
    float SetConnectionStrengthFromStatus(EConnectionStatus ConnectionStatus)
    {
        switch (ConnectionStatus)
        {
            case EConnectionStatus::DoorClosed:
                ConnectionStrength = 0.15f;
                return 0.15f;
            case EConnectionStatus::DoorOpen:
                ConnectionStrength = 0.3f;
                return 0.3f;
            case EConnectionStatus::NoDoor:
                ConnectionStrength = 0;
                return 0;
            default:
                return 0;
        }
    }
};

USTRUCT(BlueprintType)
struct FGraphEdgePtr
{
    GENERATED_BODY()
    
    UGraphEdge* Edge;

    operator UGraphEdge*() const { return Edge; }
};

FORCEINLINE uint32 GetTypeHash(const UGraphEdge& Edge)
{
    return HashCombine(::GetTypeHash(Edge.RoomStartID), ::GetTypeHash(Edge.RoomEndID));
}

FORCEINLINE bool operator==(const UGraphEdge& A, const UGraphEdge& B)
{
    return A.RoomStartID == B.RoomStartID && A.RoomEndID == B.RoomEndID;
}

FORCEINLINE bool operator==(const FGraphEdgePtr& A, const FGraphEdgePtr& B)
{
    return *A.Edge == *B.Edge;
}

FORCEINLINE uint32 GetTypeHash(const FGraphEdgePtr& A)
{
    return ::GetTypeHash(*A.Edge);
}

USTRUCT(BlueprintType)
struct FGraphEdgeSet
{
    GENERATED_BODY()

public:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Building Graph")
    TSet<FGraphEdgePtr> Edges;
};

UCLASS(BlueprintType)
class FIRESIMULATION_API UBuildingGraph : public UObject
{
public:
    GENERATED_BODY()

    UFUNCTION(BlueprintCallable, Category="Building Graph")
    void PrepareGraphToWork();

    UFUNCTION(BlueprintCallable, Category="Building Graph")
    void AddRoom(const URoomNode* Room);

    UFUNCTION(BlueprintCallable, Category="Building Graph")
    void AddConnection(const URoomNode* StartRoom, const URoomNode* EndRoom, EConnectionStatus ConnectionStatus);

    UFUNCTION(BlueprintCallable, Category = "Building Graph")
    const TMap<int32, URoomNode*>& GetRooms() const;

    UFUNCTION(BlueprintCallable, Category = "Building Graph")
    void CalculateFireDynamicsForSecond(int32 TimeInSeconds, float TimeStep = 1.0f);

    UFUNCTION(BlueprintCallable, Category = "Building Graph")
    bool MergeToSourceRoom(int32 TargetRoomID);

    // Убирает дым во всех комнатах
    UFUNCTION(BlueprintCallable, Category = "Building Graph")
    void ClearAllRooms();

protected:
    UPROPERTY(VisibleAnywhere, Category = "Building Graph")
    TMap<int32, URoomNode*> Rooms;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Building Graph")
    TMap<int32, FGraphEdgeSet> OutgoingConnections;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Building Graph")
    TMap<int32, FGraphEdgeSet> IncomingConnections;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Building Graph")
    int32 SourceRoomID;

    UFUNCTION(BlueprintCallable, Category = "Building Graph")
    void FindSourceRoomId();

    UFUNCTION(BlueprintCallable, Category = "Building Graph")
    FFireDynamicsParameters CalculateFireDynamicsForRoom(URoomNode* Room, float CurrentTime);

    UFUNCTION(BlueprintCallable, Category = "Building Graph")
    bool TopologicalSort();

    UFUNCTION(BlueprintCallable, Category = "Building Graph")
    void UpdateGraphConnectionsAfterMergeToSourceRoom(int32 TargetRoomID);
};