#include "GridOriginActor.h"
#include "Components/SphereComponent.h"

AGridOriginActor::AGridOriginActor()
{
    SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
    RootComponent = SphereComponent;
    SphereComponent->InitSphereRadius(100.0f);
    SphereComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    static ConstructorHelpers::FObjectFinder<UMaterial> MaterialFinder(TEXT("Material'/Engine/EngineMaterials/DefaultMaterial.DefaultMaterial'"));
    if (MaterialFinder.Succeeded())
    {
        SphereComponent->SetMaterial(0, MaterialFinder.Object);
    }
}

void AGridOriginActor::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
    Super::PostEditChangeProperty(PropertyChangedEvent);

    // Здесь можно добавить вашу логику обработки после изменения свойства.
}

void AGridOriginActor::OnConstruction(const FTransform& Transform)
{
    Super::OnConstruction(Transform);

    // Здесь можно добавить логику инициализации актора.
}

void AGridOriginActor::BeginPlay()
{
    Super::BeginPlay();

    // Ваша логика инициализации здесь
}
