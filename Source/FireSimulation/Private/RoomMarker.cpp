// RoomMarker.cpp
#include "RoomMarker.h"
#include "Components/BoxComponent.h"

ARoomMarker::ARoomMarker()
{
    PrimaryActorTick.bCanEverTick = true;

    // Initialize the BoxComponent to represent the room boundaries
    RoomBounds = CreateDefaultSubobject<UBoxComponent>(TEXT("RoomBounds"));
    RootComponent = RoomBounds;
}

void ARoomMarker::BeginPlay()
{
    Super::BeginPlay();
}
