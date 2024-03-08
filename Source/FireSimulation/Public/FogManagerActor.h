#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HAL/CriticalSection.h"
#include "BuildingGraph.h"
#include "FogManagerActor.generated.h"

UCLASS()
class FIRESIMULATION_API AFogManagerActor : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    AFogManagerActor(const FObjectInitializer& ObjectInitializer);

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    static AFogManagerActor* GetInstance();

    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // После игры возвращает сцену к прежнему виду
    UFUNCTION(BlueprintCallable)
    void RestoreScene();

    void UpdateFog();
    void SetVisibility(URoomNode room, float meters);
    void OnEndPIE(const bool bIsSimulating);


private:    
    UBuildingGraph* graph;
    float TimeAccumulator;
    float TotalTime;

    // Статический экземпляр для синглтона.
    static AFogManagerActor* Instance;
};
