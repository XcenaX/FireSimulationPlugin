#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FireSimulationComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FIRESIMULATIONPLUGIN_API UFireSimulationComponent : public UActorComponent
{
    GENERATED_BODY()

public:    
    UFireSimulationComponent();

protected:
    virtual void BeginPlay() override;

public:    
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    // Добавьте методы для управления симуляцией здесь
    void StartFireAtLocation(const FVector& Location);
    void SetFireTexture(UTexture2D* Texture);
    void LoadMaterialFromJson(const FString& FilePath);
};
