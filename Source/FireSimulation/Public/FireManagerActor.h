#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HAL/CriticalSection.h"
#include <RoomMarker.h>
#include <FogManagerActor.h>
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

    bool Contains(TArray<FGridCell> List, FGridCell Cell);

    int CalculateFP(int x, int y, int z);

    // Показывает скрытые акторы; Тушит весь огонь
    UFUNCTION(BlueprintCallable)
    void RestoreScene();

    void OnEndPIE(const bool bIsSimulating);


private:
    TArray<FGridCell> CheckList;
    TArray<FGridCell> FireList;
    TArray<FGridCell> NewList;
    int32 Threads;

    FCriticalSection ListMutex;

    TArray<FVector> CheckListRemovalIndices;
    TArray<FVector> NewListRemovalIndices;
    TArray<FVector> FireListRemovalIndices;

    AFireGridManager* GridManager;
    AFogManagerActor* FogManager;

    float TimeAccumulator;


};
