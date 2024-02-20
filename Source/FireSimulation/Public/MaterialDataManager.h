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
    const FMaterialData* GetMaterialData(const FString& MaterialName) const;

    const TArray<TSharedPtr<FString>>& GetMaterialNames() const;

private:
    // ��������� ����������� ��� ���������
    FMaterialDataManager() {}

    // ��� ������ � ����������
    TMap<FString, FMaterialData> MaterialDataMap;

    TArray<TSharedPtr<FString>> MaterialNamesCache;
};
