#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
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
    GENERATED_BODY()

public:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Fire Dynamics")
    float A; // �������������� ����� �������� ������

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Fire Dynamics")
    float N; // �������������� ����� �������� ������.

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Fire Dynamics")
    float GasReleasePerMeterBurn; // ����� ����, ������������� ��� �������� �� ������� �������.

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Fire Dynamics")
    float LimitGasDensity; // ������ ��������� ������� �����.

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Fire Dynamics")
    float LimitGasTemperature; // ������ ����������� ������� �����.

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Fire Dynamics")
    float LimitSmokeExtinctionCoefficient; // ������ ������������ ��������� ����.

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Fire Dynamics")
    float LimitVisibility; // ������ ��������� � �������� ������.

    FCalculatedParameters()
        : A(0.f), N(0.f), GasReleasePerMeterBurn(0.f), LimitGasDensity(0.f),
        LimitGasTemperature(0.f), LimitSmokeExtinctionCoefficient(0.f), LimitVisibility(0.f)
    {
    }
};

USTRUCT(BlueprintType)
struct FFireDynamicsParameters
{
    GENERATED_BODY()

public:
    // ���������� ���������� �����
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Fire Dynamics")
    float BurnedMass;

    // ��������� ������� ����� � ���������
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Fire Dynamics")
    float GasDensity;

    // ����������� ������� ����� � ���������
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Fire Dynamics")
    float GasTemperature;

    // ����������� ��������� ����
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Fire Dynamics")
    float SmokeExtinctionCoefficient;

    // ��������� � ���������
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Fire Dynamics")
    float Visibility;

    // ����������� �� ��������� ��� ������������� ��������
    FFireDynamicsParameters()
        : BurnedMass(0.f), GasDensity(0.f), GasTemperature(0.f),
        SmokeExtinctionCoefficient(0.f), Visibility(0.f) {}
};

UCLASS(BlueprintType)
class URoomNode : public UObject
{
    GENERATED_BODY()

public: // ��� ����� �������� ������ �� ����� ������� (RoomMarker)
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Room")
    int32 RoomID;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Room")
    bool IsGasSource;                                                   // ����������� ������� ��������

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Room")
    float CombustionCompletenessCoefficient;                            // ����������� ������� ��������

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Room")
    float HeatAbsorptionCoefficient;                                    // ����������� ���������������

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Room")
    float StartTemperature;                                             // ��������� �����������

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Room")
    float InitialGasDensity;                                            // ��������� ��������� ������� ����� � ���������

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Room")
    float Cp;                                                           // �������� ������������ ��� ���������� ��������

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Room")
    float RoomVolume;                                                   // ����� ���������

    URoomNode();

    UFUNCTION(BlueprintCallable, Category = "Room")
    FCalculatedParameters GetCalculatedParameters() const;

    UFUNCTION(BlueprintCallable, Category = "Room")
    void UpdateFireDynamics(const FFireDynamicsParameters& NewParams);

    UFUNCTION(BlueprintCallable, Category = "Room")
    FFireDynamicsParameters GetFireDynamics() const;

    UFUNCTION(BlueprintCallable, Category = "Room")
    FCalculatedParameters InitializeCalculatedParams();

protected:
    float heat_of_combustion_;                               // ������� ��������.
    float linear_flame_speed_rate_;                          // �������� �������� ��������������� ������.
    float specific_fuel_burn_rate_;                          // �������� �������� ��������� ������� ��������.
    float smoke_forming_ability_;
    FCalculatedParameters calculated_params_;                // ������������ ���������, ���������� �� ��������� ����������.
    FFireDynamicsParameters fire_dynamics_;          // ������� ��������� ������������ ���������� ������.
};

USTRUCT(BlueprintType)
struct FGraphEdge
{
    GENERATED_BODY()

public: // ��� ����� �������� ������ �� ����� ���������� ����� (DoorComponent)
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Door")
    int32 RoomStartID;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Door")
    int32 RoomEndID;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Door")
    EConnectionStatus ConnectionStatus;

    FGraphEdge() : RoomStartID(-1), RoomEndID(-1), ConnectionStatus(EConnectionStatus::DoorClosed) {}

    float GetConnectionStrength() const
    {
        switch (ConnectionStatus)
        {
            case EConnectionStatus::DoorClosed:
                return 0.8f;
            case EConnectionStatus::DoorOpen:
                return 0.6f;
            case EConnectionStatus::NoDoor:
                return 0.4f;
            default:
                return 0;
        }
    }
};

USTRUCT(BlueprintType)
struct FGraphEdgeArray
{
    GENERATED_BODY()

public:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Building Graph")
    TArray<FGraphEdge> Edges;
};

UCLASS()
class UBuildingGraph : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category="Building Graph")
    void PrepareGraphToWork();

    UFUNCTION(BlueprintCallable, Category="Building Graph")
    void AddRoom(const URoomNode* Room);

    UFUNCTION(BlueprintCallable, Category="Building Graph")
    void AddConnection(const URoomNode* StartRoom, const URoomNode* EndRoom, EConnectionStatus ConnectionStatus);

    UFUNCTION(BlueprintCallable, Category = "Building Graph")
    const TMap<int32, URoomNode*>& GetRooms() const;

    UFUNCTION(BlueprintCallable, Category = "Building Graph")
    void CalculateFireDynamicsForSecond(float TimeInSeconds, float TimeStep = 1.0f);

    UFUNCTION(BlueprintCallable, Category = "Building Graph")
    void MergeToSourceRoom(int32 TargetRoomID);

protected:
    UPROPERTY(VisibleAnywhere, Category = "Building Graph")
    TMap<int32, URoomNode*> Rooms;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Building Graph")
    TMap<int32, FGraphEdgeArray> OutgoingConnections;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Building Graph")
    TMap<int32, FGraphEdgeArray> IncomingConnections;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Building Graph")
    int32 SourceRoomID;

    UFUNCTION(BlueprintCallable, Category = "Building Graph")
    int32 FindSourceRoomId();

    UFUNCTION(BlueprintCallable, Category = "Building Graph")
    FFireDynamicsParameters CalculateFireDynamicsForRoom(URoomNode* Room, float CurrentTime);

    UFUNCTION(BlueprintCallable, Category = "Building Graph")
    void TopologicalSortUtil(int32 RoomID, TMap<int32, bool>& Visited, TArray<int32>& Stack);

    UFUNCTION(BlueprintCallable, Category = "Building Graph")
    void TopologicalSort();

    UFUNCTION(BlueprintCallable, Category = "Building Graph")
    void UpdateGraphConnectionsAfterMergeToSourceRoom(int32 TargetRoomID);
};