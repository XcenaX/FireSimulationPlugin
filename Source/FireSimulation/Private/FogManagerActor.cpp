#include "FogManagerActor.h"
#include "RoomMarker.h"
#include "DoorComponent.h"
#include "BuildingGraph.h"
#include <MaterialData.h>

AFogManagerActor* AFogManagerActor::Instance = nullptr;

AFogManagerActor* AFogManagerActor::GetInstance()
{
    if (!Instance)
    {
        Instance = NewObject<AFogManagerActor>();
        Instance->AddToRoot(); // Предотвратить уничтожение сборщиком мусора
    }
    return Instance;
}

AFogManagerActor::AFogManagerActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    PrimaryActorTick.bCanEverTick = true;

    // Создаем подобъект UBuildingGraph с использованием ObjectInitializer.CreateDefaultSubobject
    graph = ObjectInitializer.CreateDefaultSubobject<UBuildingGraph>(this, TEXT("BuildingGraph"));
    if (!graph)
    {
        // Обработка ошибки, если объект не был создан
        UE_LOG(LogTemp, Error, TEXT("Failed to create UBuildingGraph subobject."));
    }
}

void AFogManagerActor::BeginPlay()
{
    Super::BeginPlay();

    // TODO
    // Инициализировать граф, считать со сцены все маркеры комнат и дверей и заполнить его.
    // graph.PrepareGraphToWork();

    FEditorDelegates::EndPIE.AddUObject(this, &AFogManagerActor::OnEndPIE);
}

// После завершения игры в редакторе возвращаем все сгоревшие акторы на место и тушим пожар
void AFogManagerActor::OnEndPIE(const bool bIsSimulating)
{
    UE_LOG(LogTemp, Warning, TEXT("GAME ENDED"));
    RestoreScene();
}


void AFogManagerActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Суммируем прошедшее время
    TimeAccumulator += DeltaTime;

    // Проверяем, прошла ли секунда
    if (TimeAccumulator >= 1.0f)
    {
        TotalTime += 1.0f;
        UpdateFog();
        TimeAccumulator -= 1.0f;
    }
}


void AFogManagerActor::UpdateFog()
{
    // LOG something
    // UE_LOG(LogTemp, Warning, TEXT("CheckList: %d; FireList: %d; NewList: %d"), CheckList.Num(), FireList.Num(), NewList.Num());
    // graph->CalculateFireDynamicsForSecond(TotalTime);
}


void AFogManagerActor::SetVisibility(URoomNode room, float meters) // Меняет видимость в комнате
{
    // У каждой комнаты должнна быть ссылка на ассет дыма. Для смены видимости в комнате надо как-то менять этот ассет
}


void AFogManagerActor::RestoreScene() { // Возвращает сцену к прежнему виду после завершения игры

}