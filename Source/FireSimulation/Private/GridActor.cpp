#include "GridActor.h"
#include <Components/BoxComponent.h>

AGridActor::AGridActor()
{
    GridBounds = CreateDefaultSubobject<UBoxComponent>(TEXT("RoomBounds"));
    RootComponent = GridBounds;
}

void AGridActor::OnConstruction(const FTransform& Transform)
{
    Super::OnConstruction(Transform);
}

void AGridActor::BeginPlay()
{
    Super::BeginPlay();
}
