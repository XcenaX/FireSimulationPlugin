// RoomMarker.cpp
#include "RoomMarker.h"
#include "FireSimulationComponent.h"
#include "Components/BoxComponent.h"
#include "UnrealEd.h"
#include <MaterialDataManager.h>

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
{ // ¬ысчитывает средние значени€ параметров дл€ этой комнаты
    
    FMaterialData AverageMaterialData;
    int ActorCount = 0;
    UWorld* World = GetWorld();    

    // »нициализируем средние значени€ нул€ми
    AverageMaterialData.BurningRate = 0.0f;
    AverageMaterialData.CarbonDioxide_kg_per_kg = 0.0f;
    AverageMaterialData.CarbonMonoxide_kg_per_kg = 0.0f;
    AverageMaterialData.HydrogenChloride_kg_per_kg = 0.0f;
    AverageMaterialData.LinearFlameSpeed = 0.0f;
    AverageMaterialData.LowestHeatOfCombustion_kJ_per_kg= 0.0f;
    AverageMaterialData.OxygenConsumption_kg_per_kg = 0.0f;
    AverageMaterialData.SmokeGeneration = 0.0f;    

    if (!World) return AverageMaterialData;
    if (!RoomBounds) return AverageMaterialData;

    FVector RoomCenter = RoomBounds->GetComponentLocation();
    FVector RoomSize = RoomBounds->GetScaledBoxExtent(); // –азмер границы в одну сторону от центра
    FCollisionShape Box = FCollisionShape::MakeBox(RoomSize);

    FCollisionQueryParams Params;
    Params.bTraceComplex = true;
    Params.bReturnPhysicalMaterial = false;

    FCollisionQueryParams QueryParams;
    QueryParams.bReturnPhysicalMaterial = false;

    TArray<FHitResult> HitResults;
    //World->SweepMultiByChannel(HitResults, RoomCenter, RoomCenter, FQuat::Identity, ECC_WorldStatic, Box, Params);
    
    TArray<FOverlapResult> OverlapResults;
    World->OverlapMultiByChannel(OverlapResults, RoomCenter, FQuat::Identity, ECC_WorldStatic, Box, QueryParams);

    for (const FOverlapResult& Hit : OverlapResults)
    {
        AActor* HitActor = Hit.GetActor();

        UFireSimulationComponent* FireComp = HitActor ? HitActor->FindComponentByClass<UFireSimulationComponent>() : nullptr;
        if (FireComp)
        {
            const FMaterialData* ActorMaterialData = FMaterialDataManager::Get().GetMaterialData(*FireComp->SelectedMaterial);
            
            AverageMaterialData.LowestHeatOfCombustion_kJ_per_kg += ActorMaterialData->LowestHeatOfCombustion_kJ_per_kg * FireComp->Mass;
            AverageMaterialData.BurningRate += ActorMaterialData->BurningRate * FireComp->Mass;
            AverageMaterialData.CarbonDioxide_kg_per_kg += ActorMaterialData->CarbonDioxide_kg_per_kg * FireComp->Mass;
            AverageMaterialData.CarbonMonoxide_kg_per_kg += ActorMaterialData->CarbonMonoxide_kg_per_kg * FireComp->Mass;
            AverageMaterialData.HydrogenChloride_kg_per_kg += ActorMaterialData->HydrogenChloride_kg_per_kg * FireComp->Mass;
            AverageMaterialData.LinearFlameSpeed += ActorMaterialData->LinearFlameSpeed * FireComp->Mass;
            AverageMaterialData.OxygenConsumption_kg_per_kg += ActorMaterialData->OxygenConsumption_kg_per_kg * FireComp->Mass;
            AverageMaterialData.SmokeGeneration += ActorMaterialData->SmokeGeneration * FireComp->Mass;
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

float ARoomMarker::GetRoomVolume() { // ¬озвращает площадь комнаты
    if (RoomBounds)
    {
        FVector BoxSize = RoomBounds->GetScaledBoxExtent();

        float Length = BoxSize.X * 2 / 100;
        float Width = BoxSize.Y * 2 / 100;
        float Height = BoxSize.Z * 2 / 100;

        float SurfaceArea = 2 * (Length * Width + Width * Height + Height * Length);
        return SurfaceArea;
    }

    return 0.0f;
}

bool ARoomMarker::IsGasSource()
{
    UWorld* World = GetWorld();
    if (!World) return false;
    if (!RoomBounds) return false;

    FVector RoomCenter = RoomBounds->GetComponentLocation();
    FVector RoomSize = RoomBounds->GetScaledBoxExtent(); // –азмер границы в одну сторону от центра
    FCollisionShape Box = FCollisionShape::MakeBox(RoomSize);

    FCollisionQueryParams Params;
    Params.bTraceComplex = true;
    Params.bReturnPhysicalMaterial = false;

    TArray<FHitResult> HitResults;
    World->SweepMultiByChannel(HitResults, RoomCenter, RoomCenter, FQuat::Identity, ECC_WorldStatic, Box, Params);

    for (const FHitResult& Hit : HitResults)
    {
        AActor* HitActor = Hit.GetActor();

        UFireSimulationComponent* FireComp = HitActor ? HitActor->FindComponentByClass<UFireSimulationComponent>() : nullptr;
        if (FireComp && FireComp->IsBurning)
        {
            return true;
        }
    }
    
    return false;
}

TArray<AActor*> ARoomMarker::GetActors() {
    UWorld* World = GetWorld();

    TArray<AActor*> Actors;

    if (!World || !RoomBounds) return Actors;

    FVector RoomCenter = RoomBounds->GetComponentLocation();
    FVector RoomSize = RoomBounds->GetScaledBoxExtent(); // –азмер границы в одну сторону от центра
    FCollisionShape Box = FCollisionShape::MakeBox(RoomSize);

    FCollisionQueryParams Params;
    Params.bTraceComplex = true;
    Params.bReturnPhysicalMaterial = false;
    
	FCollisionQueryParams QueryParams;
	QueryParams.bReturnPhysicalMaterial = false;

    TArray<FHitResult> HitResults;
    TArray<FOverlapResult> OverlapResults;
//    World->SweepMultiByChannel(HitResults, RoomCenter, RoomCenter, FQuat::Identity, ECC_WorldStatic, Box, Params);
    World->OverlapMultiByChannel(OverlapResults, RoomCenter, FQuat::Identity, ECC_WorldStatic, Box, QueryParams);

    for (const FOverlapResult& Hit : OverlapResults)
    {
        AActor* HitActor = Hit.GetActor();

        UFireSimulationComponent* FireComp = HitActor ? HitActor->FindComponentByClass<UFireSimulationComponent>() : nullptr;
        if (FireComp && !FireComp->IsWall)
        {
            Actors.Add(HitActor);
        }
    }
    return Actors;
}