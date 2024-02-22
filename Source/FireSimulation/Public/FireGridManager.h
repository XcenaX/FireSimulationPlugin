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

    // Инициализация сетки на основе размера мира и размера куба сетки.
    UFUNCTION(BlueprintCallable)
    void InitializeGrid(int32 CubesPerDimension, float GridLength, const FVector& GridOrigin);

    // Визуализация сетки.
    UFUNCTION(BlueprintCallable)
    void DrawGrid(bool bVisible);

    // Заполнение сетки акторами с компонентом FireSimulationComponent.
    UFUNCTION(BlueprintCallable)
    void PopulateGridWithActors(UWorld* World);

    // Получить экземпляр менеджера сетки.
    static UFireGridManager* GetInstance();

private:
    // Размер одного куба в сетке.
    float GridCellSize;

    // Трехмерный массив ячеек.
    TArray<TArray<TArray<FGridCell>>> Grid;

    FVector GridOrigin;

    // Вспомогательная функция для определения индекса ячейки по мировым координатам.
    bool GetCellIndex(const FVector& Location, int32& OutX, int32& OutY, int32& OutZ) const;

    // Статический экземпляр для синглтона.
    static UFireGridManager* Instance;
};