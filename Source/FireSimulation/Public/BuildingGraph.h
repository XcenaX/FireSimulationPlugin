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
    float A; // Характеристика схемы развития пожара

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Fire Dynamics")
    float N; // Характеристика схемы развития пожара.

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Fire Dynamics")
    float GasReleasePerMeterBurn; // Объем газа, выделяющегося при сгорании на единицу площади.

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Fire Dynamics")
    float LimitGasDensity; // Предел плотности газовой среды.

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Fire Dynamics")
    float LimitGasTemperature; // Предел температуры газовой среды.

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Fire Dynamics")
    float LimitSmokeExtinctionCoefficient; // Предел коэффициента затухания дыма.

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Fire Dynamics")
    float LimitVisibility; // Предел видимости в условиях пожара.

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
    // Количество выгоревшей массы
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Fire Dynamics")
    float BurnedMass;

    // Плотность газовой среды в помещении
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Fire Dynamics")
    float GasDensity;

    // Температура газовой среды в помещении
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Fire Dynamics")
    float GasTemperature;

    // Коэффициент затухания дыма
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Fire Dynamics")
    float SmokeExtinctionCoefficient;

    // Видимость в помещении
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Fire Dynamics")
    float Visibility;

    // Конструктор по умолчанию для инициализации значений
    FFireDynamicsParameters()
        : BurnedMass(0.f), GasDensity(0.f), GasTemperature(0.f),
        SmokeExtinctionCoefficient(0.f), Visibility(0.f) {}
};

UCLASS(BlueprintType)
class URoomNode : public UObject
{
    GENERATED_BODY()

public: // Тут нужно добавить ссылку на актор комнаты (RoomMarker)
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Room")
    int32 RoomID;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Room")
    bool IsGasSource;                                                   // Коэффициент полноты сгорания

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Room")
    float CombustionCompletenessCoefficient;                            // Коэффициент полноты сгорания

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Room")
    float HeatAbsorptionCoefficient;                                    // Коэффициент теплопоглощения

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Room")
    float StartTemperature;                                             // Начальная температура

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Room")
    float InitialGasDensity;                                            // Начальная плотность газовой среды в помещении

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Room")
    float Cp;                                                           // Удельная теплоемкость при постоянном давлении

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Room")
    float RoomVolume;                                                   // Объем помещения

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
    float heat_of_combustion_;                               // Теплота сгорания.
    float linear_flame_speed_rate_;                          // Линейная скорость распространения пожара.
    float specific_fuel_burn_rate_;                          // Удельная скорость выгорания горючей нагрузки.
    float smoke_forming_ability_;
    FCalculatedParameters calculated_params_;                // Рассчитанные параметры, основанные на начальных параметрах.
    FFireDynamicsParameters fire_dynamics_;          // История изменений динамических параметров пожара.
};

USTRUCT(BlueprintType)
struct FGraphEdge
{
    GENERATED_BODY()

public: // тут нужно добавить ссылку на актор компонента двери (DoorComponent)
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