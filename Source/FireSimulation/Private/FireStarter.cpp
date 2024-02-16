#include "FireStarter.h"

// Sets default values
AFireStarter::AFireStarter()
{
    // Set this actor to call Tick() every frame.
    PrimaryActorTick.bCanEverTick = true;

    // Инициализация начальной точки, можно задать дефолтное значение
    StartPoint = FVector(0.0f, 0.0f, 0.0f);

    // Инициализация текстуры распространения, по умолчанию nullptr
    SpreadTexture = nullptr;
}

// Called when the game starts or when spawned
void AFireStarter::BeginPlay()
{
    Super::BeginPlay();
    
    // Здесь может быть ваш код для инициализации или запуска клеточных автоматов
}

// Called every frame
void AFireStarter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Здесь может быть ваш код для обновления состояния клеточных автоматов
}
