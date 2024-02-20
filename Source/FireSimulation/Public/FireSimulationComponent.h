#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "FireSimulationComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FIRESIMULATION_API UFireSimulationComponent : public USceneComponent
{
    GENERATED_BODY()

public:    
    UFireSimulationComponent();

protected:
    virtual void BeginPlay() override;

public:
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    // Методы для управления симуляцией
    void StartFireAtLocation(const FVector& Location);
    void SetFireTexture(UTexture2D* Texture);

    // Материал объекта, нужен для расчетов распространения огня и дыма
    UPROPERTY(config, meta = (Hidden))
    FString SelectedMaterial;

    // Свойство означает является ли этот обьект точкой возгорания
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fire Simulation")
    bool IsBurning;

    void UpdateSelectedMaterial(const FString& NewMaterialName);
    FString GetSelectedMaterial();
};
