#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "FireSimulationComponent.h"
#include "RoomMarker.generated.h"

UCLASS()
class FIRESIMULATION_API ARoomMarker : public AActor
{
    GENERATED_BODY()
    
public:    
    ARoomMarker();

protected:
    virtual void BeginPlay() override;

public:    
    UPROPERTY(VisibleAnywhere, Category="Room")
    UBoxComponent* RoomBounds;

    FMaterialData CalculateAverageMaterialData();

    float GetRoomVolume();

    bool IsGasSource();

    // Custom properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Room")
    int32 RoomID = -1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Room")
    float CombustionCompletenessCoefficient = 0.87;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Room")
    float HeatAbsorptionCoefficient = 0.95;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Room")
    float StartTemperature = 293;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Room")
    float InitialGasDensity = 1.21;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Room")
    float Cp = 1.03;

    // Массив ParticleSystem тумана для комнаты. (Один Particle System тумана имеет высоту 20, 
    // для комнаты с высотой Z нужно будет N партиклов 
    // где N = Z / (20 + offset))
    // offset расстояение между партиклами (по умолчанию = высоте партикла, тоесть 20)    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Effects")
    TArray<UParticleSystemComponent*> FogEmitters;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Effects")
    TArray<UMaterialInstanceDynamic*> DynamicMaterials;

};
