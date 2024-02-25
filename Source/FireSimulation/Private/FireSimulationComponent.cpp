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
<<<<<<< Updated upstream
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
=======
    SelectedMaterial = NewMaterialName;
>>>>>>> Stashed changes
}

FString UFireSimulationComponent::GetSelectedMaterial()
{
<<<<<<< Updated upstream
	return SelectedMaterial;
=======
    return SelectedMaterial;
}

// функция которая не позволяет одновременно установить IsWall = true и IsBurning = true
void UFireSimulationComponent::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
    Super::PostEditChangeProperty(PropertyChangedEvent);

    FName PropertyName = (PropertyChangedEvent.Property != nullptr) ? PropertyChangedEvent.Property->GetFName() : NAME_None;

    if (PropertyName == GET_MEMBER_NAME_CHECKED(UFireSimulationComponent, IsWall))
    {
        if (IsWall)
        {
            // Если IsWall установлено в true, IsDoor должно быть false
            IsDoor = false;
        }
    }
    else if (PropertyName == GET_MEMBER_NAME_CHECKED(UFireSimulationComponent, IsDoor))
    {
        if (IsDoor)
        {
            // Если IsDoor установлено в true, IsWall должно быть false
            IsWall = false;
        }
    }
>>>>>>> Stashed changes
}