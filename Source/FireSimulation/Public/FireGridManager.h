#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include <GridActor.h>
#include <FireSimulationComponent.h>
#include "FireGridManager.generated.h"

#define EMPTY 0
#define BURNING 1   
#define BURNT 2

USTRUCT(BlueprintType)
struct FGridCell
{
    GENERATED_BODY()

public:
    // Ссылка на актора в ячейке. Может быть nullptr, если ячейка пуста.
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    AActor* OccupyingActor = nullptr;
    int32 Status = EMPTY;
    int32 x;
    int32 y;
    int32 z;
    int32 time = 0; // время которое горит ячейка (секунд)
    float mass = 0; // масса кокретной ячейки (не объекта в целом) (кг)
    AActor* FireActor = nullptr;
    TArray<FGridCell*> Neighbours;

    bool operator==(const FGridCell& Other) const
    {
        return x == Other.x && y == Other.y && z == Other.z;
    }

    friend uint32 GetTypeHash(const FGridCell& Cell)
    {
        return HashCombine(HashCombine(GetTypeHash(Cell.x), GetTypeHash(Cell.y)), GetTypeHash(Cell.z));
    }
};

/**
 * Класс для управления трехмерной сеткой распространения огня.
 */
UCLASS(BlueprintType)
class FIRESIMULATION_API UFireGridManager : public UObject
{
    GENERATED_BODY()

public:
    UFireGridManager();

    // Инициализация сетки на основе количества элементов в одном измерении.
    UFUNCTION(BlueprintCallable)
    void InitializeGrid(UWorld* World, AGridActor* GridActor, int32 CubesPerDimension, int32 Threads, int32 FireSize, UObject* FireParticle);
 
    // Заполнение сетки акторами с компонентом FireSimulationComponent. 
    UFUNCTION(BlueprintCallable)
    void PopulateGridWithActors();

    // Создает Актор огня в загоревшейся ячейке
    //UFUNCTION(BlueprintCallable)
    void CreateFireActor(FGridCell* Cell);

    // Скрывает сгоревший обьект и удаляет огонь который на нем был
    //UFUNCTION(BlueprintCallable)
    void RemoveBurntActor(FGridCell* Cell);

    void ClearGrid();

    TArray<FGridCell*> GetBurningCells();
    FGridCell& GetCell(int32 x, int32 y, int32 z);

    // Количество поток
    int Threads;
    // Размер одного элемента в сетке.
    int CellSize;
    // Размеры сетки.
    int ElementsAmountX;
    int ElementsAmountY;
    int ElementsAmountZ;
    // Размер партикла огня
    int FireParticleSize;

    // Класс актора огня который будет создаваться на месте загоревшейся ячейки    
    UObject* SelectedParticleFire;

    TMap<AActor*, int> ActorCellsCount;
    TMap<AActor*, UFireSimulationComponent*> ActorToFireCompMap;

private:
    UWorld* World;
    AGridActor* GridActor;
    // Трехмерный массив ячеек.
    TArray<FGridCell> Grid;
};