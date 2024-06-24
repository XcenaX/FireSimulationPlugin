#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include <GridActor.h>
#include <FireSimulationComponent.h>
#include "FireGridManager.generated.h"

#define EMPTY 0
#define BURNING 1   
#define BURNT 2

// Struct representing a grid cell in the fire simulation
USTRUCT(BlueprintType)
struct FGridCell
{
    GENERATED_BODY()

public:
    // Pointer to the actor occupying this cell and can be nullptr if the cell is empty
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    AActor* OccupyingActor = nullptr;
    // Status of the cell (EMPTY, BURNING, or BURNT)
    int32 Status = EMPTY;
    // Coordinates of the cell
    int32 x;
    int32 y;
    int32 z;
    // Time the cell has been burning (in seconds)
    int32 time = 0;
    // Mass of the specific cell (in kg)
    float mass = 0;
    // Pointer to the fire actor in this cell
    AActor* FireActor = nullptr;
    TArray<FGridCell*> Neighbours;

    // Equality operator to compare two grid cells
    bool operator==(const FGridCell& Other) const
    {
        return x == Other.x && y == Other.y && z == Other.z;
    }

    // Hash function for the grid cell
    friend uint32 GetTypeHash(const FGridCell& Cell)
    {
        return HashCombine(HashCombine(GetTypeHash(Cell.x), GetTypeHash(Cell.y)), GetTypeHash(Cell.z));
    }

    // Remove a neighbor from the list of neighbors
    void RemoveNeighbour(FGridCell* Neighbour) {
        int32 Index = Neighbours.Find(Neighbour);
        if (Index != INDEX_NONE) {
            Neighbours.RemoveAt(Index);
        }
    }
};

/**
 * Class for managing a 3D grid for fire spread simulation
 */
UCLASS(BlueprintType)
class FIRESIMULATION_API UFireGridManager : public UObject
{
    GENERATED_BODY()

public:
    UFireGridManager();

    // Initialize the grid based on the number of elements in each dimension
    UFUNCTION(BlueprintCallable)
    void InitializeGrid(UWorld* World, AGridActor* GridActor, int32 CubesPerDimension, int32 Threads, int32 FireSize, UObject* FireParticle);
 
    // Populate the grid with actors that have a FireSimulationComponent
    UFUNCTION(BlueprintCallable)
    void PopulateGridWithActors();

    // Create a fire actor in a burning cell
    void CreateFireActor(FGridCell* Cell);

    // Hide a burnt object and remove the fire actor that was on it
    void RemoveBurntActor(FGridCell* Cell);

    void ClearGrid();

    TArray<FGridCell*> GetBurningCells();
    FGridCell& GetCell(int32 x, int32 y, int32 z);

    // Number of threads
    int Threads;
    // Size of one cell in the grid
    int CellSize;
    // Dimensions of the grid
    int ElementsAmountX;
    int ElementsAmountY;
    int ElementsAmountZ;
    // Size of the fire particle
    int FireParticleSize;

    // Class of the fire actor that will be created in burning cells
    UObject* SelectedParticleFire;

    // Maps to track the number of cells occupied by actors and their corresponding FireSimulationComponents
    TMap<AActor*, int> ActorCellsCount;
    TMap<AActor*, UFireSimulationComponent*> ActorToFireCompMap;

private:
    UWorld* World;
    AGridActor* GridActor;
    // 3D array of grid cells
    TArray<FGridCell> Grid;
    virtual void BeginDestroy() override;
};