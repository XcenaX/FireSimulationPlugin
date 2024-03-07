#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
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
};

/**
 * Класс для управления трехмерной сеткой распространения огня.
 */
UCLASS()
class FIRESIMULATION_API AFireGridManager : public AActor
{
    GENERATED_BODY()

public:
    AFireGridManager();

    // Инициализация сетки на основе количества элементов в одном измерении.
    UFUNCTION(BlueprintCallable)
    void InitializeGrid(int32 CubesPerDimension, int32 Threads);

    // Визуализация сетки.
    UFUNCTION(BlueprintCallable)
    void DrawGrid(bool bVisible, UWorld* World, AActor* GridActor);

    // Заполнение сетки акторами с компонентом FireSimulationComponent.
    UFUNCTION(BlueprintCallable)
    void PopulateGridWithActors(UWorld* World, AActor* GridActor);

    // Создает Актор огня в загоревшейся ячейке
    UFUNCTION(BlueprintCallable)
    void CreateFireActor(FGridCell Cell, UWorld * World);

    // Скрывает сгоревший обьект и удаляет огонь который на нем был
    UFUNCTION(BlueprintCallable)
    void RemoveBurntActor(FGridCell& Cell);

    // Получить экземпляр менеджера сетки.
    static AFireGridManager* GetInstance();

    TArray<FGridCell> GetBurningCells();

    // Трехмерный массив ячеек.
    TArray<TArray<TArray<FGridCell>>> Grid;

    // Количество элементов в сетке в одном измерении.
    float ElementsAmount;
    // Количество поток
    int Threads;
    // Класс актора огня который будет создаваться на месте загоревшейся ячейки    

    UObject* SelectedParticleFire;
    UObject* SelectedParticleFog;

    TMap<AActor*, int> ActorCellsCount;

private:
    // Статический экземпляр для синглтона.
    static AFireGridManager* Instance;
};