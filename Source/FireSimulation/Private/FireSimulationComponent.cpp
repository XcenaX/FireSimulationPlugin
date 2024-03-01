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

void UFireSimulationComponent::UpdateSelectedMaterial(FMaterialData NewMaterial)
{
	#if WITH_EDITOR
		if (GEditor)
		{
			GEditor->BeginTransaction(FText::FromString("Change Selected Material"));
			Modify();
		}
	#endif
		SelectedMaterial = NewMaterial.Name;
	#if WITH_EDITOR
		if (GEditor)
		{
			GEditor->EndTransaction();
		}
	#endif

    SelectedMaterialData = NewMaterial;
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