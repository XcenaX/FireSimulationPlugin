#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include <MaterialData.h>
#include "FireSimulationComponent.generated.h"

// FireSimulationComponent class to handle fire simulation on an object
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FIRESIMULATION_API UFireSimulationComponent : public USceneComponent
{
    GENERATED_BODY()

protected:
    virtual void BeginPlay() override;

public:
    UFireSimulationComponent();

    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    // Methods for managing the fire simulation. Starts fire at a given location
    void StartFireAtLocation(const FVector& Location);
    void SetFireTexture(UTexture2D* Texture);

	UPROPERTY(EditAnywhere, Category = "Fire Simulation", meta = (Hidden))
    FString SelectedMaterial;

    // Mass of the object (kg) (default = 10)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fire Simulation")
    float Mass;

    // Indicates whether this object is a fire source
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fire Simulation")
    bool IsBurning;

    // Indicates whether the object is a wall (walls cannot burn)
    UPROPERTY(EditAnywhere, Category = "Fire Simulation")
    bool IsWall = false;

    // Updates the selected material for the object
    void UpdateSelectedMaterial(FString NewMaterial);

    // Called when a property is changed in the editor
    virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
};
