#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MaterialManagerActor.generated.h"
#include "MaterialData.h"

UCLASS()
class FIRESIMULATION_API AMaterialManagerActor : public AActor
{
    GENERATED_BODY()

public:
    TArray<FMaterialData> MaterialsData;

    // Sets default values for this actor's properties
    AMaterialManagerActor();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    //void LoadMaterialsFromJson(const FString& FilePath);
};
