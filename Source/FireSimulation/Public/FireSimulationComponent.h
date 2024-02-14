#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MaterialData.h"
#include "FireSimulationComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FIRESIMULATIONPLUGIN_API UFireSimulationComponent : public UActorComponent
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
    UPROPERTY(EditAnywhere, Category = "Fire Simulation")
    FString MaterialDataJsonPath;

    // Массив для хранения загруженных данных о материалах
    TArray<FMaterialData> MaterialOptions;
};
