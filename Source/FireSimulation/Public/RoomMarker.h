#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
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

    // Custom properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Room")
    int32 RoomID;
};
