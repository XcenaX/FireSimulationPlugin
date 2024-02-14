#pragma once

#include "CoreMinimal.h"
#include "MaterialData.generated.h"

USTRUCT(BlueprintType)
struct FMaterialData
{
    GENERATED_BODY()

public:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Material Data")
    FString Name;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Material Data")
    float LowestHeatOfCombustion_kJ_per_kg;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Material Data")
    float LinearFlameSpeed;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Material Data")
    float BurningRate;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Material Data")
    float SmokeGeneration;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Material Data")
    float OxygenConsumption_kg_per_kg;

    // Данные о газовых эмиссиях
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Material Data")
    float CarbonDioxide_kg_per_kg;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Material Data")
    float CarbonMonoxide_kg_per_kg;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Material Data")
    float HydrogenChloride_kg_per_kg;
};
