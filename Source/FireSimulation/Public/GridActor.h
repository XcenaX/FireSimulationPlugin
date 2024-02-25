#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "GridActor.generated.h"

UCLASS()
class FIRESIMULATION_API AGridActor : public AActor
{
    GENERATED_BODY()

public:
    AGridActor();

protected:
    virtual void BeginPlay() override;
    
public:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Grid")
    UBoxComponent* GridBounds;

    virtual void OnConstruction(const FTransform& Transform) override;

#if WITH_EDITOR
    virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
};
