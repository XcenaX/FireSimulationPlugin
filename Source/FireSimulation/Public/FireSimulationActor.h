#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FireSimulationActor.generated.h"

UCLASS()
class FIRESIMULATIONPLUGIN_API AFireSimulationActor : public AActor
{
    GENERATED_BODY()
    
public:    
    AFireSimulationActor();

protected:
    virtual void BeginPlay() override;

public:    
    virtual void Tick(float DeltaTime) override;

    // Компонент симуляции огня
    UPROPERTY(VisibleAnywhere)
    class UFireSimulationComponent* FireSimulationComponent;
};
