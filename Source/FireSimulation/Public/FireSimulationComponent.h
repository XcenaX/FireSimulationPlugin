#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "MaterialData.h"
#include "FireSimulationComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FIRESIMULATION_API UFireSimulationComponent : public USceneComponent
{
    GENERATED_BODY()

public:    
    UFireSimulationComponent();

protected:
    // Вызывается при запуске игры или когда создается актор
    virtual void BeginPlay() override;

public:    
    // Вызывается каждый кадр
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    // Методы для управления симуляцией
    void StartFireAtLocation(const FVector& Location);
    void SetFireTexture(UTexture2D* Texture);

    // Метод для загрузки данных о материалах из JSON
    void LoadMaterialFromJson();

    // Путь к JSON файлу с данными о материалах
    FString MaterialDataJsonPath;
    
    // Горючий материал объекта (нужен при расчетете распространения огня и дыма)
    /*UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Fire Simulation")
    TArray<UMaterialInterface*> AvailableMaterials;*/

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Fire Simulation")
    FString SelectedMaterial;

    TArray<FString> MaterialNames;

    // Массив для хранения загруженных данных о материалах
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Fire Simulation")
    TArray<FMaterialData> MaterialOptions;

    void InitializeMaterialNames();

    void UpdateSelectedMaterial(const FString& NewMaterialName);
    FString GetCurrentMaterialName();

};
