#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HAL/CriticalSection.h"
#include "FireManagerActor.generated.h"

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

    // Основная функция для инициализации распространения огня
    UFUNCTION(BlueprintCallable, Category = "Fire Management")
    void InitializeFireSpread();

    // Функция обновления распространения огня
    UFUNCTION(BlueprintCallable, Category = "Fire Management")
    void UpdateFireSpread();

    void processCheckList(int32 StartIndex, int32 EndIndex, TArray<FVector>& CoordsToRemove);
    void processNewList(int32 StartIndex, int32 EndIndex, TArray<FVector>& CoordsToRemove);
    void processFireList(int32 StartIndex, int32 EndIndex, TArray<FVector>& CoordsToRemove);
    void parallelProcessList(TArray<FGridCell>& List, TFunction<void(int32, int32, TArray<FVector>&)> ProcessFunction, TArray<FVector>& GlobalCoordsToRemove);
    void RemoveCellsByCoords(TArray<FGridCell>& List, TArray<FVector>& CoordsToRemove);
    int CalculateFP(TArray<TArray<TArray<FGridCell>>> cells, int x, int y, int z);

    AActor* CreateFireActor(UClass* ActorClass, const FVector& Location);

private:
    TArray<FGridCell> CheckList;
    TArray<FGridCell> FireList;
    TArray<FGridCell> NewList;
    int32 Threads;
    TArray<TArray<TArray<FGridCell>>> Cells;
    FCriticalSection ListMutex;

    TArray<FVector> CheckListRemovalIndices;
    TArray<FVector> NewListRemovalIndices;
    TArray<FVector> FireListRemovalIndices;

    UFireGridManager* GridManager;

    float TimeAccumulator;


};
