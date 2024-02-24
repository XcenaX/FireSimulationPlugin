#include "FireSimulationComponent.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonSerializer.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Interfaces/IPluginManager.h"
#if WITH_EDITOR
#include "Editor.h"
#endif

UFireSimulationComponent::UFireSimulationComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.
	PrimaryComponentTick.bCanEverTick = true;
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

void UFireSimulationComponent::UpdateSelectedMaterial(const FString& NewMaterialName)
{
#if WITH_EDITOR
	if (GEditor)
	{
		GEditor->BeginTransaction(FText::FromString("Change Selected Material"));
		Modify();
	}
#endif
	SelectedMaterial = NewMaterialName;
#if WITH_EDITOR
	if (GEditor)
	{
		GEditor->EndTransaction();
	}
#endif

	// Пример дополнительной логики (псевдокод):
	// UMaterialInterface* Material = LoadMaterialByName(SelectedMaterialName);
	// if (Material)
	// {
	//     ApplyMaterialToMesh(Material); // Функция, которая применяет материал к мешу
	// }
}

FString UFireSimulationComponent::GetSelectedMaterial()
{
	return SelectedMaterial;
}