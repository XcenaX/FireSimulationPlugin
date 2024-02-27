#pragma once

#include "CoreMinimal.h"
#include "MaterialData.h"

class FIRESIMULATION_API FMaterialDataManager
{
public:
    // Получение экземпляра синглтона
    static FMaterialDataManager& Get()
    {
        static FMaterialDataManager Instance;
        return Instance;
    }

    // Загрузка данных о материалах из JSON файла
    bool LoadMaterialData();

    // Получение данных о материале по имени
    FMaterialData* GetMaterialData(FString MaterialName);

    const TArray<TSharedPtr<FString>>& GetMaterialNames() const;

private:
    // Приватный конструктор для синглтона
    FMaterialDataManager() {}

    // Кэш данных о материалах
    TMap<FString, FMaterialData> MaterialDataMap;

    TArray<TSharedPtr<FString>> MaterialNamesCache;
};
