#include "FireSimulationComponent.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonSerializer.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Interfaces/IPluginManager.h"
#if WITH_EDITOR
#include "Editor.h"
#endif
#include <MaterialData.h>

UFireSimulationComponent::UFireSimulationComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.
	PrimaryComponentTick.bCanEverTick = true;
    Mass = 10;
}

void UFireSimulationComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UFireSimulationComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Обновление симуляции огня здесь
}

void UFireSimulationComponent::StartFireAtLocation(const FVector& Location)
{
	// Логика для начала симуляции огня в заданной точке
}

void UFireSimulationComponent::SetFireTexture(UTexture2D* Texture)
{
	// Установка текстуры огня
}

void UFireSimulationComponent::UpdateSelectedMaterial(FMaterialData* NewMaterial)
{
    SelectedMaterial.BurningRate                        = NewMaterial->BurningRate;
    SelectedMaterial.CarbonDioxide_kg_per_kg            = NewMaterial->CarbonDioxide_kg_per_kg;
    SelectedMaterial.CarbonMonoxide_kg_per_kg           = NewMaterial->CarbonMonoxide_kg_per_kg;
    SelectedMaterial.HydrogenChloride_kg_per_kg         = NewMaterial->HydrogenChloride_kg_per_kg;
    SelectedMaterial.LinearFlameSpeed                   = NewMaterial->LinearFlameSpeed;
    SelectedMaterial.LowestHeatOfCombustion_kJ_per_kg   = NewMaterial->LowestHeatOfCombustion_kJ_per_kg;
    SelectedMaterial.Name                               = NewMaterial->Name;
    SelectedMaterial.OxygenConsumption_kg_per_kg        = NewMaterial->OxygenConsumption_kg_per_kg;
    SelectedMaterial.SmokeGeneration                    = NewMaterial->SmokeGeneration;
}


// функция которая не позволяет одновременно установить IsWall = true и IsBurning = true
void UFireSimulationComponent::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
    Super::PostEditChangeProperty(PropertyChangedEvent);

    FName PropertyName = (PropertyChangedEvent.Property != nullptr) ? PropertyChangedEvent.Property->GetFName() : NAME_None;

    if (PropertyName == GET_MEMBER_NAME_CHECKED(UFireSimulationComponent, IsWall))
    {
        IsBurning = false;        
    }
    else if (PropertyName == GET_MEMBER_NAME_CHECKED(UFireSimulationComponent, IsBurning))
    {
        IsWall = false;        
    }
}