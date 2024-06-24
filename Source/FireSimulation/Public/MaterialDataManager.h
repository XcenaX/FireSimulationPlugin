#pragma once

#include "CoreMinimal.h"
#include "MaterialData.h"

class FIRESIMULATION_API FMaterialDataManager
{
public:
    // Provides access to the singleton instance of the manager
    static FMaterialDataManager& Get()
    {
        static FMaterialDataManager Instance;
        return Instance;
    }

    // Loads material data from a source (e.g., file or database)
    bool LoadMaterialData();

    // Retrieves material data by material name
    const FMaterialData* GetMaterialData(const FString& MaterialName) const;

    // Retrieves a list of material names
    const TArray<TSharedPtr<FString>>& GetMaterialNames() const;

private:
    // Private constructor to enforce singleton pattern
    FMaterialDataManager() {}

    // Map storing material data, keyed by material name
    TMap<FString, FMaterialData> MaterialDataMap;

    // Cache of material names for quick access
    TArray<TSharedPtr<FString>> MaterialNamesCache;
};
