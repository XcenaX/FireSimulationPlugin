// В заголовочном файле вашего актора
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "GridOriginActor.generated.h"

UCLASS()
class FIRESIMULATION_API AGridOriginActor : public AActor
{
    GENERATED_BODY()

public:
    AGridOriginActor();

protected:
    virtual void BeginPlay() override;
    
    UPROPERTY(VisibleAnywhere)
    USphereComponent* SphereComponent;
public:
    virtual void OnConstruction(const FTransform& Transform) override;

#if WITH_EDITOR
    virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
};
