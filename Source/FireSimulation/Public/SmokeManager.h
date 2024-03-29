#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HAL/CriticalSection.h"
#include "BuildingGraph.h"
#include "DoorComponent.h"
#include "SmokeManager.generated.h"

UCLASS(BlueprintType)
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

    TMap<FString, ARoomMarker*> ActorsLocation; // Нужно для проверки перекинулся ли огонь в другую комнату
    TMap<int32, bool> RoomsStatus; // Горит комната или нет

    void UpdateSmoke();

    bool GetRoomStatusForActor(FString Name);
    void SetRoomStatus(int32 RoomID, bool Status);
    int32 GetRoomIdForActor(FString Name);

    UBuildingGraph* graph; 

    int32 TotalTime;

private:
    TArray<ARoomMarker*> Rooms;
    TArray<UDoorComponent*> Doors;
    float TimeAccumulator;
};
