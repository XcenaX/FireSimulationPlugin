#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FireGridManager.generated.h"

USTRUCT(BlueprintType)
struct FGridCell
{
    GENERATED_BODY()

public:
    // Ссылка на актора в ячейке. Может быть nullptr, если ячейка пуста.
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    AActor* OccupyingActor = nullptr;
};

/**
 * Класс для управления трехмерной сеткой распространения огня.
 */
UCLASS()
class FIRESIMULATION_API UFireGridManager : public UObject
{
    GENERATED_BODY()

public:
    UFireGridManager();

    // Инициализация сетки на основе количества элементов в одном измерении.
    UFUNCTION(BlueprintCallable)
    void InitializeGrid(int32 CubesPerDimension);

    // Визуализация сетки.
    UFUNCTION(BlueprintCallable)
    void DrawGrid(bool bVisible, UWorld* World, AActor* GridActor);

    // Заполнение сетки акторами с компонентом FireSimulationComponent.
    UFUNCTION(BlueprintCallable)
    void PopulateGridWithActors(UWorld* World, AActor* GridActor);

    // Получить экземпляр менеджера сетки.
    static UFireGridManager* GetInstance();

private:
    // Количество элементов в сетке в одном измерении.
    float ElementsAmount;

    // Трехмерный массив ячеек.
    TArray<TArray<TArray<FGridCell>>> Grid;

    // Статический экземпляр для синглтона.
    static UFireGridManager* Instance;
};