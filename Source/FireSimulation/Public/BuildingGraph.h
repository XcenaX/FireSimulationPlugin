#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BuildingGraph.generated.h"

UENUM(BlueprintType)
enum class EDoorStatus : uint8
{
    Closed      UMETA(DisplayName = "Closed"),
    Open        UMETA(DisplayName = "Open"),
    NoDoor      UMETA(DisplayName = "No Door")
};

USTRUCT(BlueprintType)
struct FRoomNode
{
    GENERATED_BODY()

public:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Room")
    int32 RoomID;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Room")
    float Area;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Room")
    TArray<int32> Neighbors;

    FRoomNode() : RoomID(-1), Area(0.0f) {}
};

USTRUCT(BlueprintType)
struct FDoorEdge
{
    GENERATED_BODY()

public:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Door")
    int32 RoomAID;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Door")
    int32 RoomBID;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Door")
    EDoorStatus DoorStatus;

    FDoorEdge() : RoomAID(-1), RoomBID(-1), DoorStatus(EDoorStatus::Closed) {}

    float GetConnectionStrength() const
    {
        switch (DoorStatus)
        {
            case EDoorStatus::Closed:
                return 0.8f;
            case EDoorStatus::Open:
                return 0.6f;
            case EDoorStatus::NoDoor:
                return 0.4f;
            default:
                return 1.0f;
        }
    }
};

UCLASS()
class UBuildingGraph : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category="Building Graph")
    void InitializeGraph();

    UFUNCTION(BlueprintCallable, Category="Building Graph")
    void AddRoom(const FRoomNode& Room);

    UFUNCTION(BlueprintCallable, Category="Building Graph")
    void AddDoor(const FDoorEdge& Door);

    UFUNCTION(BlueprintCallable, Category="Building Graph")
    void CalculateRoomAreas();

protected:
    UPROPERTY(VisibleAnywhere, Category="Building Graph")
    TArray<FRoomNode> Rooms;

    UPROPERTY(VisibleAnywhere, Category="Building Graph")
    TArray<FDoorEdge> Doors;
};
