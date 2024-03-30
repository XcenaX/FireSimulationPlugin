#include "DoorComponent.h"
#include "Components/BoxComponent.h"

UDoorComponent::UDoorComponent()
{
    DoorBounds = CreateDefaultSubobject<UBoxComponent>(TEXT("DoorBounds"));
    bIsOpen = false;
}

void UDoorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UDoorComponent::ToggleDoorState()
{
    bIsOpen = !bIsOpen;

    OnDoorStateChangedDelegate.Broadcast(this, bIsOpen);
}