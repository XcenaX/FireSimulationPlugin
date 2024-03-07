#include "FogManagerActor.h"
#include "RoomMarker.h"
#include "DoorComponent.h"
#include "BuildingGraph.h"
#include <MaterialData.h>

AFogManagerActor::AFogManagerActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    PrimaryActorTick.bCanEverTick = true;

    // ������� ��������� UBuildingGraph � �������������� ObjectInitializer.CreateDefaultSubobject
    graph = ObjectInitializer.CreateDefaultSubobject<UBuildingGraph>(this, TEXT("BuildingGraph"));
    if (!graph)
    {
        // ��������� ������, ���� ������ �� ��� ������
        UE_LOG(LogTemp, Error, TEXT("Failed to create UBuildingGraph subobject."));
    }
}

void AFogManagerActor::BeginPlay()
{
    Super::BeginPlay();

    // TODO
    // ���������������� ����, ������� �� ����� ��� ������� ������ � ������ � ��������� ���.
    // graph.PrepareGraphToWork();    

    FEditorDelegates::EndPIE.AddUObject(this, &AFogManagerActor::OnEndPIE);
}

// ����� ���������� ���� � ��������� ���������� ��� ��������� ������ �� ����� � ����� �����
void AFogManagerActor::OnEndPIE(const bool bIsSimulating)
{
    UE_LOG(LogTemp, Warning, TEXT("GAME ENDED"));
    RestoreScene();
}


void AFogManagerActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // ��������� ��������� �����
    TimeAccumulator += DeltaTime;

    // ���������, ������ �� �������
    if (TimeAccumulator >= 1.0f)
    {        
        UpdateFog();        
        TimeAccumulator -= 1.0f;
    }
}


void AFogManagerActor::UpdateFog()
{
    // LOG something
    // UE_LOG(LogTemp, Warning, TEXT("CheckList: %d; FireList: %d; NewList: %d"), CheckList.Num(), FireList.Num(), NewList.Num());
    
    // ������ ���������� ����
}


void AFogManagerActor::SetVisibility(URoomNode room, float meters) // ������ ��������� � �������
{
    // � ������ ������� ������� ���� ������ �� ����� ����. ��� ����� ��������� � ������� ���� ���-�� ������ ���� �����
}


void AFogManagerActor::RestoreScene() { // ���������� ����� � �������� ���� ����� ���������� ����

}