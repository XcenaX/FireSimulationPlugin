#include "RoomMarker.h"
#include "FireSimulationComponent.h"
#include "Components/BoxComponent.h"
#include "UnrealEd.h"
#include <MaterialDataManager.h>

ARoomMarker::ARoomMarker()
{
	PrimaryActorTick.bCanEverTick = true;

	RoomBounds = CreateDefaultSubobject<UBoxComponent>(TEXT("RoomBounds"));
	RootComponent = RoomBounds;
}

void ARoomMarker::BeginPlay()
{
	Super::BeginPlay();
}

FMaterialData ARoomMarker::CalculateAverageMaterialData()
{
	FMaterialData AverageMaterialData;
	if (!RoomBounds) return AverageMaterialData;

	TArray<AActor*> Actors = GetActors();
	if (Actors.Num() <= 0) return AverageMaterialData;

	UWorld* World = GetWorld();
	if (!World) return AverageMaterialData;

	float TotalMass = 0.0f;
	int32 TotalActors = 0;
	for (const AActor* Actor : Actors)
	{
		UFireSimulationComponent* FireComp = Actor ? Actor->FindComponentByClass<UFireSimulationComponent>() : nullptr;
		if (FireComp)
		{
			const FMaterialData* ActorMaterialData = FMaterialDataManager::Get().GetMaterialData(*FireComp->SelectedMaterial);

			AverageMaterialData.LowestHeatOfCombustion_kJ_per_kg += ActorMaterialData->LowestHeatOfCombustion_kJ_per_kg * FireComp->Mass;
			AverageMaterialData.BurningRate += ActorMaterialData->BurningRate;
			AverageMaterialData.CarbonDioxide_kg_per_kg += ActorMaterialData->CarbonDioxide_kg_per_kg * FireComp->Mass;
			AverageMaterialData.CarbonMonoxide_kg_per_kg += ActorMaterialData->CarbonMonoxide_kg_per_kg * FireComp->Mass;
			AverageMaterialData.HydrogenChloride_kg_per_kg += ActorMaterialData->HydrogenChloride_kg_per_kg * FireComp->Mass;
			AverageMaterialData.LinearFlameSpeed += ActorMaterialData->LinearFlameSpeed;
			AverageMaterialData.OxygenConsumption_kg_per_kg += ActorMaterialData->OxygenConsumption_kg_per_kg * FireComp->Mass;
			AverageMaterialData.SmokeGeneration += ActorMaterialData->SmokeGeneration;
			TotalMass += FireComp->Mass;
			TotalActors++;
		}
	}

	if (TotalMass > 0 && TotalActors > 0)
	{
		AverageMaterialData.LowestHeatOfCombustion_kJ_per_kg /= TotalMass;
		AverageMaterialData.BurningRate /= TotalActors;
		AverageMaterialData.CarbonDioxide_kg_per_kg /= TotalMass;
		AverageMaterialData.CarbonMonoxide_kg_per_kg /= TotalMass;
		AverageMaterialData.HydrogenChloride_kg_per_kg /= TotalMass;
		AverageMaterialData.LinearFlameSpeed /= TotalActors;
		AverageMaterialData.OxygenConsumption_kg_per_kg /= TotalMass;
		AverageMaterialData.SmokeGeneration /= TotalActors;
	}

	return AverageMaterialData;
}

float ARoomMarker::GetRoomVolume(float UnitsPerMeter) {
	if (RoomBounds)
	{
		FVector BoxSize = RoomBounds->GetScaledBoxExtent();
		float ConversionFactor = 1.0f / UnitsPerMeter;
		return (BoxSize.X * 2 * ConversionFactor) * (BoxSize.Y * 2 * ConversionFactor) * (BoxSize.Z * 2 * ConversionFactor);
	}

	return 0.0f;
}

bool ARoomMarker::IsGasSource(TArray<AActor*> Actors)
{
	if (!RoomBounds) return false;

	for (const AActor* Actor : Actors)
	{
		UFireSimulationComponent* FireComp = Actor ? Actor->FindComponentByClass<UFireSimulationComponent>() : nullptr;
		if (FireComp && FireComp->IsBurning)
		{
			return true;
		}
	}

	return false;
}

bool ARoomMarker::IsGasSource()
{
	if (!RoomBounds) return false;

	TArray<AActor*> Actors = GetActors();
	if (Actors.Num() <= 0) return false;

	for (const AActor* Actor : Actors)
	{
		UFireSimulationComponent* FireComp = Actor ? Actor->FindComponentByClass<UFireSimulationComponent>() : nullptr;
		if (FireComp && FireComp->IsBurning)
			return true;
	}

	return false;
}

TArray<AActor*> ARoomMarker::GetActors()
{
	TArray<AActor*> Actors;
	if (!RoomBounds) return Actors;

	UWorld* World = GetWorld();
	if (!World) return Actors;

	FVector RoomCenter = RoomBounds->GetComponentLocation();
	FVector RoomSize = RoomBounds->GetScaledBoxExtent();
	FCollisionShape Box = FCollisionShape::MakeBox(RoomSize);

	FCollisionQueryParams QueryParams;
	QueryParams.bReturnPhysicalMaterial = false;

	TArray<FOverlapResult> OverlapResults;
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