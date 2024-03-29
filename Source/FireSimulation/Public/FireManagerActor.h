#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HAL/CriticalSection.h"
#include <SmokeManager.h>
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

    void InitializeFireSpread();

    // Функция обновления распространения огня вручную. Эта функция высчитывает распространение один раз. Может пригодится если нужно быстро проверить пожар
    UFUNCTION(BlueprintCallable, Category = "Fire Management")
    void UpdateFireSpread();

    void InitializeGrid(int32 CellSize, int32 Threads, int32 FireDistance);

    // Функция запуска распространения огня, пожар распространяется каждую секунду
    UFUNCTION(BlueprintCallable, Category = "Fire Management")
    void StartFireThread(int32 CellSize, int32 NewThreads, int32 FireDistance);

    // Функция остановки распространения огня
    UFUNCTION(BlueprintCallable, Category = "Fire Management")
    void StopFireThread();

    void processCheckList(int32 StartIndex, int32 EndIndex, TArray<FVector>& CoordsToRemove);
    void processNewList(int32 StartIndex, int32 EndIndex, TArray<FVector>& CoordsToRemove);
    void processFireList(int32 StartIndex, int32 EndIndex, TArray<FVector>& CoordsToRemove);

    void parallelProcessList(TArray<FGridCell*>& List, TFunction<void(int32, int32, TArray<FVector>&)> ProcessFunction, TArray<FVector>& GlobalCoordsToRemove);
    void RemoveCellsByCoords(TArray<FGridCell*>& List, TArray<FVector>& CoordsToRemove);

    bool Contains(TArray<FGridCell*> List, FGridCell Cell);
    bool Contains(TArray<FGridCell*> List, FGridCell* Cell);

    int CalculateFP(FGridCell* Cell);
    
    // Показывает скрытые акторы; Тушит весь огонь
    UFUNCTION(BlueprintCallable)
    void RestoreScene();

    void OnEndPIE(const bool bIsSimulating);


private:
    TArray<FGridCell*> CheckList;
    TArray<FGridCell*> FireList;
    TArray<FGridCell*> NewList;
    TArray<FGridCell*> BurntList;
    int32 Threads;
    bool JobDone = true; // Завершены ли расчеты распространения огня для текущей секунды

    bool Stop = false;

    FCriticalSection ListMutex;

    TArray<FVector> CheckListRemovalIndices;
    TArray<FVector> NewListRemovalIndices;
    TArray<FVector> FireListRemovalIndices;

    AFireGridManager* GridManager;
    USmokeManager* SmokeManager;

    float TimeAccumulator;


};
