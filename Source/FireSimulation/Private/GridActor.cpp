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

    // Здесь можно добавить логику инициализации актора.
}

void AGridActor::BeginPlay()
{
    Super::BeginPlay();

    // Ваша логика инициализации здесь
}
