#include "MaterialDataManager.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Serialization/JsonSerializer.h"
#include "Interfaces/IPluginManager.h"

bool FMaterialDataManager::LoadMaterialData()
{
    FString JsonString;
    FString PluginName = TEXT("FireSimulation");
    FString PluginPath = IPluginManager::Get().FindPlugin(PluginName)->GetBaseDir();
    FString FilePath = PluginPath + TEXT("/Content/Data/materials.json");

    if (!FFileHelper::LoadFileToString(JsonString, *FilePath))
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to load JSON file: %s"), *FilePath);
        return false;
    }

    TArray<TSharedPtr<FJsonValue>> JsonArray;
    TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonString);

    if (!FJsonSerializer::Deserialize(Reader, JsonArray))
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to parse JSON file: %s"), *FilePath);
        return false;
    }

    for (auto& Value : JsonArray)
    {
        TSharedPtr<FJsonObject> JsonObject = Value->AsObject();
        if (JsonObject.IsValid())
        {
            FMaterialData MaterialData;
            MaterialData.Name = JsonObject->GetStringField("Name");
            MaterialData.LowestHeatOfCombustion_kJ_per_kg = JsonObject->GetNumberField("LowestHeatOfCombustion_kJ_per_kg");
            MaterialData.LinearFlameSpeed = JsonObject->GetNumberField("LinearFlameSpeed");
            MaterialData.BurningRate = JsonObject->GetNumberField("BurningRate");
            MaterialData.SmokeGeneration = JsonObject->GetNumberField("SmokeGeneration");
            MaterialData.OxygenConsumption_kg_per_kg = JsonObject->GetNumberField("OxygenConsumption_kg_per_kg");
            MaterialData.CarbonDioxide_kg_per_kg = JsonObject->GetObjectField("GasEmission")->GetNumberField("CarbonDioxide_kg_per_kg");
            MaterialData.CarbonMonoxide_kg_per_kg = JsonObject->GetObjectField("GasEmission")->GetNumberField("CarbonMonoxide_kg_per_kg");
            MaterialData.HydrogenChloride_kg_per_kg = JsonObject->GetObjectField("GasEmission")->GetNumberField("HydrogenChloride_kg_per_kg");

            MaterialDataMap.Add(MaterialData.Name, MaterialData);
        }
    }
    UE_LOG(LogTemp, Warning, TEXT("Loaded %d materials from %s"), MaterialDataMap.Num(), *FilePath);
    MaterialNamesCache.Empty();
    for (const auto& Pair : MaterialDataMap)
    {
        MaterialNamesCache.Add(MakeShared<FString>(Pair.Key));
    }
    return true;
}

FMaterialData FMaterialDataManager::GetMaterialData(FString MaterialName)
{
    FMaterialData NewMaterialData;
    FMaterialData* FoundMaterialData = MaterialDataMap.Find(MaterialName);
    if (FoundMaterialData)
    {
        NewMaterialData.BurningRate = FoundMaterialData->BurningRate;
        NewMaterialData.CarbonDioxide_kg_per_kg = FoundMaterialData->CarbonDioxide_kg_per_kg;
        NewMaterialData.CarbonMonoxide_kg_per_kg = FoundMaterialData->CarbonMonoxide_kg_per_kg;
        NewMaterialData.HydrogenChloride_kg_per_kg = FoundMaterialData->HydrogenChloride_kg_per_kg;
        NewMaterialData.LinearFlameSpeed = FoundMaterialData->LinearFlameSpeed;
        NewMaterialData.LowestHeatOfCombustion_kJ_per_kg = FoundMaterialData->LowestHeatOfCombustion_kJ_per_kg;
        NewMaterialData.OxygenConsumption_kg_per_kg = FoundMaterialData->OxygenConsumption_kg_per_kg;
        NewMaterialData.SmokeGeneration = FoundMaterialData->SmokeGeneration;
        return NewMaterialData;
    }
    else
    {
        return NewMaterialData;
    }
}

const TArray<TSharedPtr<FString>>& FMaterialDataManager::GetMaterialNames() const
{
    return MaterialNamesCache;
}
