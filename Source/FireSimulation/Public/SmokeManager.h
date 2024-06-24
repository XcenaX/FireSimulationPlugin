#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HAL/CriticalSection.h"
#include "BuildingGraph.h"
#include "DoorComponent.h"
#include "SmokeManager.generated.h"

UCLASS()
class FIRESIMULATION_API USmokeManager : public UObject
{
    GENERATED_BODY()

public:
    USmokeManager();

    void Initialize(UWorld* InWorld);

    FString EnumToString(EConnectionStatus Status)
    {
        const UEnum* EnumType = FindObject<UEnum>(ANY_PACKAGE, TEXT("EConnectionStatus"), true);
        if (!EnumType)
        {
            return FString("Invalid");
        }

        return EnumType->GetNameStringByValue((int64)Status);
    }

    void UpdateSmoke();

    bool GetRoomStatusForActor(FString Name);
    void SetRoomStatus(int32 RoomID, bool Status);
    int32 GetRoomIdForActor(FString Name);

    UFUNCTION(meta = (Hidden))
    void OnDoorStateChanged(UDoorComponent* Door, bool bIsOpen);

    UPROPERTY(meta = (Hidden))
    UBuildingGraph* graph;

    TMap<FString, ARoomMarker*> ActorsLocation;
    TMap<int32, bool> RoomsStatus;

    int32 TotalTime;

    UFUNCTION(BlueprintCallable, Category = "Building Graph")
    void Cleanup();

    bool CorrectlySetuped();

    TArray<FString> BadRooms; // rooms with no actors that have FireSimulationComponent

private:
    TArray<ARoomMarker*> Rooms;
    TArray<UDoorComponent*> Doors;
    float UnitsPerMeter;
    virtual void BeginDestroy() override;
};
