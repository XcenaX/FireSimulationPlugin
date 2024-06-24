#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HAL/CriticalSection.h"
#include <SmokeManager.h>
#include "FireManagerActor.generated.h"

// FireManagerActor class that manages the fire simulation in the game
UCLASS()
class FIRESIMULATION_API AFireManagerActor : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    AFireManagerActor();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:    
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    void InitializeFireSpread();

    // Manually updates the fire spread calculation. Useful for quickly checking the fire spread.
    UFUNCTION(BlueprintCallable, Category = "Fire Management")
    void UpdateFireSpread();

    void InitializeGrid(int32 CellSize, int32 Threads, int32 FireDistance, UObject* FireParticle);

    // Starts the fire spread thread, causing the fire to spread every second
    UFUNCTION(BlueprintCallable, Category = "Fire Management")
    void StartFireThread(int32 CellSize, int32 NewThreads, int32 FireDistance, UObject* FireParticle);

    // Stops the fire spread thread
    UFUNCTION(BlueprintCallable, Category = "Fire Management")
    void StopFireThread();

    // Processes the checklist of cells to be checked for fire spread
    void processCheckList(int32 StartIndex, int32 EndIndex, TArray<FVector>& CoordsToRemove);

    // Processes the new list of cells that have caught fire
    void processNewList(int32 StartIndex, int32 EndIndex, TArray<FVector>& CoordsToRemove);

    // Processes the fire list of cells that are currently burning
    void processFireList(int32 StartIndex, int32 EndIndex, TArray<FVector>& CoordsToRemove);

    // Parallel processing of a list of cells
    void parallelProcessList(TArray<FGridCell*>& List, TFunction<void(int32, int32, TArray<FVector>&)> ProcessFunction, TArray<FVector>& GlobalCoordsToRemove);
    void RemoveCellsByCoords(TArray<FGridCell*>& List, TArray<FVector>& CoordsToRemove);

    bool Contains(TArray<FGridCell*> List, FGridCell Cell);
    bool Contains(TArray<FGridCell*> List, FGridCell* Cell);

    int CalculateFP(FGridCell* Cell);
    float GetSpreadFactor(float LinearSpeed) const;

    // Restores the scene by showing hidden actors and extinguishing all fire
    UFUNCTION(BlueprintCallable)
    void RestoreScene();

    void OnEndPIE(const bool bIsSimulating);


private:
    TArray<FGridCell*> CheckList;
    TArray<FGridCell*> FireList;
    TArray<FGridCell*> NewList;
    TArray<FGridCell*> BurntList;
    int32 Threads;

    // Flag indicating whether the job for the current second is done
    bool JobDone = true;

    // Flag to stop the fire spread thread
    bool Stop = false;

    // Mutex for thread-safe access to the lists
    FCriticalSection ListMutex;

    // Indices of cells to be removed from the lists
    TArray<FVector> CheckListRemovalIndices;
    TArray<FVector> NewListRemovalIndices;
    TArray<FVector> FireListRemovalIndices;

    // Grid manager for handling the fire grid
    UPROPERTY()
    UFireGridManager* GridManager;

    // Smoke manager for handling smoke effects
    UPROPERTY()
    USmokeManager* SmokeManager;

    // Accumulator for tracking time
    float TimeAccumulator;

    // Units per meter conversion factor
    float UnitsPerMeter;
    int TotalSimulationTime;
};
