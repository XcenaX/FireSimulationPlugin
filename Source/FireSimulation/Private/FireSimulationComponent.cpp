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
    Mass = 10.0;
}

void UFireSimulationComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UFireSimulationComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UFireSimulationComponent::StartFireAtLocation(const FVector& Location)
{
}

void UFireSimulationComponent::SetFireTexture(UTexture2D* Texture)
{
}

void UFireSimulationComponent::UpdateSelectedMaterial(FString NewMaterial)
{
	#if WITH_EDITOR
		if (GEditor)
		{
			GEditor->BeginTransaction(FText::FromString("Change Selected Material"));
			Modify();
		}
	#endif
		SelectedMaterial = NewMaterial;
	#if WITH_EDITOR
		if (GEditor)
		{
			GEditor->EndTransaction();
		}
	#endif
}


// A function that prevents setting IsWall = true and IsBurning = true at the same time
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