#pragma once

#include "CoreMinimal.h"
#include "MaterialData.h"

class FIRESIMULATION_API FMaterialDataManager
{
public:
    // ��������� ���������� ���������
    static FMaterialDataManager& Get()
    {
        static FMaterialDataManager Instance;
        return Instance;
    }

    // �������� ������ � ���������� �� JSON �����
    bool LoadMaterialData();

    // ��������� ������ � ��������� �� �����
    FMaterialData* GetMaterialData(FString MaterialName);

    const TArray<TSharedPtr<FString>>& GetMaterialNames() const;

private:
    // ��������� ����������� ��� ���������
    FMaterialDataManager() {}

    // ��� ������ � ����������
    TMap<FString, FMaterialData> MaterialDataMap;

    TArray<TSharedPtr<FString>> MaterialNamesCache;
};
