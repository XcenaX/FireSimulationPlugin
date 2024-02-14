#include "FireSimulationComponent.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonSerializer.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"

UFireSimulationComponent::UFireSimulationComponent()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.
    PrimaryComponentTick.bCanEverTick = true;
}

void UFireSimulationComponent::BeginPlay()
{
    Super::BeginPlay();
    LoadMaterialFromJson();
}

void UFireSimulationComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    // Обновление симуляции огня здесь
}

void UFireSimulationComponent::StartFireAtLocation(const FVector& Location)
{
    // Логика для начала симуляции огня в заданной точке
}

void UFireSimulationComponent::SetFireTexture(UTexture2D* Texture)
{
    // Установка текстуры огня
}

void UFireSimulationComponent::LoadMaterialFromJson()
{
    FString JsonString;
    FString FilePath = FPaths::ProjectContentDir() + TEXT("Data/materials.json");

    if (FFileHelper::LoadFileToString(JsonString, *FullPath))
    {
        TArray<TSharedPtr<FJsonValue>> JsonArray;
        TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonString);

        if (FJsonSerializer::Deserialize(Reader, JsonArray))
        {
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

                    // Добавление данных о материале в массив
                    MaterialOptions.Add(MakeShareable(new FMaterialData(MaterialData)));
                }
            }
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("Failed to parse JSON file: %s"), *FullPath);
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to load JSON file: %s"), *FullPath);
    }
}
