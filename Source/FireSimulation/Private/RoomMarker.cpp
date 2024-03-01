// RoomMarker.cpp
#include "RoomMarker.h"
#include "FireSimulationComponent.h"
#include "Components/BoxComponent.h"
#include "UnrealEd.h"

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

FMaterialData ARoomMarker::CalculateAverageMaterialData()
{ // Высчитывает средние значения параметров для этой комнаты
    TArray<AActor*> ActorsInRoom;
    FVector BoxExtent = RoomBounds->GetScaledBoxExtent();
    FVector BoxCenter = RoomBounds->GetComponentLocation();
    FMaterialData AverageMaterialData;
    int ActorCount = 0;
    UWorld* World = GEditor->GetEditorWorldContext().World();


    // Инициализируем средние значения нулями
    AverageMaterialData.BurningRate = 0.0f;
    AverageMaterialData.CarbonDioxide_kg_per_kg = 0.0f;
    AverageMaterialData.CarbonMonoxide_kg_per_kg = 0.0f;
    AverageMaterialData.HydrogenChloride_kg_per_kg = 0.0f;
    AverageMaterialData.LinearFlameSpeed = 0.0f;
    AverageMaterialData.LowestHeatOfCombustion_kJ_per_kg= 0.0f;
    AverageMaterialData.OxygenConsumption_kg_per_kg = 0.0f;
    AverageMaterialData.SmokeGeneration = 0.0f;    

    // Получаем все акторы в мире
    for (TActorIterator<AActor> It(World); It; ++It)
    {
        AActor* Actor = *It;
        UFireSimulationComponent* FireComp = Actor->FindComponentByClass<UFireSimulationComponent>();
        if (FireComp && RoomBounds->IsOverlappingActor(Actor))
        {
            FMaterialData ActorMaterialData = FireComp->SelectedMaterialData;
            // Агрегация значений
            AverageMaterialData.LowestHeatOfCombustion_kJ_per_kg += ActorMaterialData.LowestHeatOfCombustion_kJ_per_kg;
            AverageMaterialData.BurningRate += ActorMaterialData.BurningRate;
            AverageMaterialData.CarbonDioxide_kg_per_kg += ActorMaterialData.CarbonDioxide_kg_per_kg;
            AverageMaterialData.CarbonMonoxide_kg_per_kg += ActorMaterialData.CarbonMonoxide_kg_per_kg;
            AverageMaterialData.HydrogenChloride_kg_per_kg += ActorMaterialData.HydrogenChloride_kg_per_kg;
            AverageMaterialData.LinearFlameSpeed += ActorMaterialData.LinearFlameSpeed;
            AverageMaterialData.OxygenConsumption_kg_per_kg += ActorMaterialData.OxygenConsumption_kg_per_kg;
            AverageMaterialData.SmokeGeneration += ActorMaterialData.SmokeGeneration;
            ActorCount++;
        }
    }

    if (ActorCount > 0)
    {
        AverageMaterialData.LowestHeatOfCombustion_kJ_per_kg /= ActorCount;
        AverageMaterialData.BurningRate /= ActorCount;
        AverageMaterialData.CarbonDioxide_kg_per_kg /= ActorCount;
        AverageMaterialData.CarbonMonoxide_kg_per_kg /= ActorCount;
        AverageMaterialData.HydrogenChloride_kg_per_kg /= ActorCount;
        AverageMaterialData.LinearFlameSpeed /= ActorCount;
        AverageMaterialData.OxygenConsumption_kg_per_kg /= ActorCount;
        AverageMaterialData.SmokeGeneration /= ActorCount;
    }

    return AverageMaterialData;
}