// FireStarter.h
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FireStarter.generated.h"

UCLASS()
class YOURPROJECTNAME_API FireStarter : public AActor
{
    GENERATED_BODY()

public:    
    // Sets default values for this actor's properties
    FireStarter();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:    
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Начальная точка для распространения клеточных автоматов
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Cellular Automaton")
    FVector StartPoint;

    // Текстура для визуализации клеточных автоматов
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Cellular Automaton")
    UTexture2D* SpreadTexture;
};
