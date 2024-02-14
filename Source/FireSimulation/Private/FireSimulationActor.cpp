#include "FireSimulationActor.h"
#include "FireSimulationComponent.h"

AFireSimulationActor::AFireSimulationActor()
{
    // Set this actor to call Tick() every frame.
    PrimaryActorTick.bCanEverTick = true;

    // Создание и присоединение компонента симуляции огня к актору
    FireSimulationComponent = CreateDefaultSubobject<UFireSimulationComponent>(TEXT("FireSimulationComponent"));
    RootComponent = FireSimulationComponent;
}

void AFireSimulationActor::BeginPlay()
{
    Super::BeginPlay();
    
    // Инициализация может быть выполнена здесь
}

void AFireSimulationActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Обновление симуляции огня, если необходимо
}
