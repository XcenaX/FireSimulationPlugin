#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <RoomMarker.h>
#include "Components/BoxComponent.h"
#include "DoorComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class FIRESIMULATION_API UDoorComponent : public USceneComponent
{
    GENERATED_BODY()

public:
    UDoorComponent();

protected:
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
    UPROPERTY(VisibleAnywhere, Category="Door")
    UBoxComponent* DoorBounds;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door")
    ARoomMarker* ConnectedRoom1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door")
    ARoomMarker* ConnectedRoom2;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Door")
    bool bIsOpen;

    UFUNCTION(BlueprintCallable, Category = "Door")
    void ToggleDoorState();
};
