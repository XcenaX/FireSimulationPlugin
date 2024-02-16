#include "MyActor.h"
#include "FireSimulationComponent.h"

AMyActor::AMyActor()
{
    // Этот актор вызывает Tick каждый кадр. Вы можете отключить это, если не нужно.
    PrimaryActorTick.bCanEverTick = true;

    // Создание и прикрепление компонента FireSimulation к актору
    UFireSimulationComponent* FireSimulationComp = CreateDefaultSubobject<UFireSimulationComponent>(TEXT("FireSimulationComponent"));
    FireSimulationComp->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

void AMyActor::BeginPlay()
{
    Super::BeginPlay();
}
