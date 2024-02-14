#include "MaterialManagerActor.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonSerializer.h"


AMaterialManagerActor::AMaterialManagerActor()
{
    // Set this actor to call Tick() every frame if needed
    PrimaryActorTick.bCanEverTick = true;
}

void AMaterialManagerActor::BeginPlay()
{
    Super::BeginPlay();
    LoadMaterialsFromJson();
}

void AMaterialManagerActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}