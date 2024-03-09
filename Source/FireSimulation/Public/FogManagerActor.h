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

    // ����� ���� ���������� ����� � �������� ����
    UFUNCTION(BlueprintCallable)
    void RestoreScene();

    void InitializeGraph(UWorld* World);

    void UpdateFog();
    void SetVisibility(URoomNode room, float meters);
    void OnEndPIE(const bool bIsSimulating);

    UBuildingGraph* graph; 

private:    
    float TimeAccumulator;
    float TotalTime;

    // ����������� ��������� ��� ���������.
    static AFogManagerActor* Instance;
};
