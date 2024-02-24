#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "FireSimulationComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FIRESIMULATION_API UFireSimulationComponent : public USceneComponent
{
    GENERATED_BODY()

protected:
    virtual void BeginPlay() override;

public:
    UFireSimulationComponent();

    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    // Методы для управления симуляцией
    void StartFireAtLocation(const FVector& Location);
    void SetFireTexture(UTexture2D* Texture);

	UPROPERTY(EditAnywhere, Category = "Fire Simulation", meta = (Hidden))
    FString SelectedMaterial;

    // Свойство означает является ли этот обьект точкой возгорания
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fire Simulation")
    bool IsBurning;

    void UpdateSelectedMaterial(const FString& NewMaterialName);
    FString GetSelectedMaterial();
};
