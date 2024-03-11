#include "CoreMinimal.h"
#include "Misc/AutomationTest.h"
#include "BuildingGraph.h"

class UBuildingGraphTestHelper : public UBuildingGraph
{
public:
	UBuildingGraphTestHelper() {}

	void TestFindSourceRoomId()
	{
		FindSourceRoomId();
	}

	TMap<int32, URoomNode*>& TestGetRooms()
	{
		return Rooms;
	}

	TMap<int32, FGraphEdgeSet>& TestGetIncomingConnections() 
	{
		return IncomingConnections;
	}

	TMap<int32, FGraphEdgeSet>& TestGetOutgoingConnections()
	{
		return OutgoingConnections;
	}

	bool TestTopologicalSort()
	{
		return TopologicalSort();
	}

	void TestResetRooms()
	{
		Rooms.Reset();
	}

	int32 TestGetSourceRoomId()
	{
		return SourceRoomID;
	}
};

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FUniqueFireSourceTest, "FireSimulation.FireSimulationTests.BuildingGraphTests.UniqueFireSourceTest", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FUniqueFireSourceTest::RunTest(const FString& Parameters)
{
	UBuildingGraphTestHelper* BuildingGraph = NewObject<UBuildingGraphTestHelper>();

	URoomNode* FirstRoom = NewObject<URoomNode>();
	FirstRoom->Initialize(1, true, 0.8f, 0.6f, 293.15f, 1.2f, 1000.0f, 50.0f, 50000.0f, 0.5f, 0.01f, 0.5f);
	BuildingGraph->AddRoom(FirstRoom);

	// Проверка, что первая комната добавлена и является источником огня
	TestTrue("First room with fire source should be added", BuildingGraph->GetRooms().Contains(1) && FirstRoom->IsGasSource);

	// Создание второй комнаты с источником огня
	URoomNode* SecondRoom = NewObject<URoomNode>();
	SecondRoom->Initialize(2, true, 0.8f, 0.6f, 293.15f, 1.2f, 1000.0f, 50.0f, 50000.0f, 0.5f, 0.01f, 0.5f);
	BuildingGraph->AddRoom(SecondRoom);

	BuildingGraph->TestFindSourceRoomId();
	TestEqual("SourceRoomID should be -1 due to multiple fire sources", BuildingGraph->TestGetSourceRoomId(), -1);

	BuildingGraph->TestResetRooms();
	BuildingGraph->TestFindSourceRoomId();
	TestEqual("SourceRoomID should be -1 as no fire sources are present", BuildingGraph->TestGetSourceRoomId(), -1);

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FTopologicalSortBranchingTest, "FireSimulation.FireSimulationTests.BuildingGraphTests.TopologicalSort.Branching", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FTopologicalSortBranchingTest::RunTest(const FString& Parameters)
{
	UBuildingGraphTestHelper* BuildingGraph = NewObject<UBuildingGraphTestHelper>();

	URoomNode* RoomC = NewObject<URoomNode>();
	RoomC->Initialize(3, false, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f);
	BuildingGraph->AddRoom(RoomC);

	URoomNode* RoomA = NewObject<URoomNode>();
	RoomA->Initialize(1, false, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f);
	BuildingGraph->AddRoom(RoomA);

	URoomNode* RoomB = NewObject<URoomNode>();
	RoomB->Initialize(2, false, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f);
	BuildingGraph->AddRoom(RoomB);

	URoomNode* RoomD = NewObject<URoomNode>();
	RoomD->Initialize(4, false, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f);
	BuildingGraph->AddRoom(RoomD);

	BuildingGraph->AddConnection(RoomA, RoomB, EConnectionStatus::DoorOpen);
	BuildingGraph->AddConnection(RoomA, RoomC, EConnectionStatus::DoorOpen);
	BuildingGraph->AddConnection(RoomB, RoomD, EConnectionStatus::DoorOpen);
	BuildingGraph->AddConnection(RoomC, RoomD, EConnectionStatus::DoorOpen);

	BuildingGraph->TestTopologicalSort();

	TMap<int32, URoomNode*> SortedRooms = BuildingGraph->TestGetRooms();

	TArray<int32> RoomIDs;
	SortedRooms.GetKeys(RoomIDs);
	int32 IndexA = RoomIDs.IndexOfByKey(1);
	int32 IndexB = RoomIDs.IndexOfByKey(2);
	int32 IndexC = RoomIDs.IndexOfByKey(3);
	int32 IndexD = RoomIDs.IndexOfByKey(4);

	// Утверждаем, что RoomD (4) должна идти после RoomB (2) и RoomC (3), и что RoomB и RoomC должны идти после RoomA (1)
	TestTrue("RoomD should come after RoomB and RoomC", IndexD > IndexB && IndexD > IndexC);
	TestTrue("RoomB and RoomC should come after RoomA", IndexB > IndexA && IndexC > IndexA);

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FTopologicalSortCycleTest, "FireSimulation.FireSimulationTests.BuildingGraphTests.TopologicalSort.Cycle", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FTopologicalSortCycleTest::RunTest(const FString& Parameters)
{
	UBuildingGraphTestHelper* BuildingGraph = NewObject<UBuildingGraphTestHelper>();

	// Добавление комнат
	URoomNode* RoomA = NewObject<URoomNode>();
	RoomA->Initialize(1, false, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f);
	BuildingGraph->AddRoom(RoomA);

	URoomNode* RoomB = NewObject<URoomNode>();
	RoomB->Initialize(2, false, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f);
	BuildingGraph->AddRoom(RoomB);

	// Создание цикла: A -> B -> A
	BuildingGraph->AddConnection(RoomA, RoomB, EConnectionStatus::DoorOpen);
	BuildingGraph->AddConnection(RoomB, RoomA, EConnectionStatus::DoorOpen);

	// Попытка выполнить топологическую сортировку
	bool bSortResult = BuildingGraph->TestTopologicalSort();

	// Утверждаем, что сортировка не удалась из-за цикла
	TestFalse("Topological sort should fail due to a cycle", bSortResult);

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FMergeRoomsTest, "FireSimulation.FireSimulationTests.BuildingGraphTests.MergeRooms", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FMergeRoomsTest::RunTest(const FString& Parameters)
{
	UBuildingGraphTestHelper* BuildingGraph = NewObject<UBuildingGraphTestHelper>();

	// Инициализация комнат
	URoomNode* FireSourceRoom = NewObject<URoomNode>(); // Очаг
	FireSourceRoom->Initialize(1, true, 0.8f, 0.6f, 293.15f, 1.2f, 1000.0f, 50.0f, 50000.0f, 0.5f, 0.01f, 0.5f);
	BuildingGraph->AddRoom(FireSourceRoom);

	TArray<URoomNode*> rooms;
	for (int i = 2; i <= 6; ++i) {
		URoomNode* Room = NewObject<URoomNode>();
		Room->Initialize(i, false, 0.9f, 0.7f, 295.15f, 1.3f, 1050.0f, 60.0f * i, 55000.0f, 0.6f, 0.02f, 0.6f);
		BuildingGraph->AddRoom(Room);
		rooms.Add(Room);
	}

	BuildingGraph->AddConnection(FireSourceRoom, rooms[0], EConnectionStatus::DoorOpen); // Очаг -> Комната 2
	BuildingGraph->AddConnection(rooms[0], rooms[1], EConnectionStatus::DoorOpen); // Комната 2 -> Комната 3
	BuildingGraph->AddConnection(rooms[1], rooms[2], EConnectionStatus::DoorOpen); // Комната 3 -> Комната 4
	BuildingGraph->AddConnection(FireSourceRoom, rooms[3], EConnectionStatus::DoorOpen); // Очаг -> Комната 5
	BuildingGraph->AddConnection(rooms[3], rooms[4], EConnectionStatus::DoorOpen); // Комната 5 -> Комната 6 (нет прямой связи с очагом)
	BuildingGraph->AddConnection(FireSourceRoom, rooms[1], EConnectionStatus::DoorClosed); // Очаг -> Комната 3 (новая прямая связь)

	BuildingGraph->PrepareGraphToWork();

	// Слияние комнаты 2 с очагом, имея прямую связь
	bool mergeResult = BuildingGraph->MergeToSourceRoom(2);
	TestTrue("Merge should succeed with direct connections from fire source", mergeResult);

	// Проверяем, что комната 2 действительно была удалена из графа
	TestFalse("Room 2 should be removed from the graph after merge", BuildingGraph->TestGetRooms().Contains(2));

	// Получаем обновленный объем комнаты-очага после слияния
	URoomNode* UpdatedFireSourceRoom = BuildingGraph->TestGetRooms().FindRef(1);
	float expectedVolumeAfterMerge = 50.0f + 60.0f * 2; // Исходный объем комнаты-очага + объем сливаемой комнаты
	TestEqual("Updated fire source room volume should be correct after merge", UpdatedFireSourceRoom->RoomVolume, expectedVolumeAfterMerge);

	// Проверяем, что все связи обновлены корректно и не возникло дублирования связей
	TMap<int32, FGraphEdgeSet>& OutgoingConnections = BuildingGraph->TestGetOutgoingConnections();
	TMap<int32, FGraphEdgeSet>& IncomingConnections = BuildingGraph->TestGetIncomingConnections();

	// Убедимся, что нет дублирующихся связей от источника огня (Room 1) к другим комнатам
	for (auto& Elem : OutgoingConnections)
	{
		if (Elem.Key == 1) // Проверяем исходящие связи именно от источника огня
		{
			TSet<int32> uniqueConnections;
			for (auto& Edge : Elem.Value.Edges)
			{
				uniqueConnections.Add(Edge.Edge->RoomEndID);
			}
			TestEqual("There should be no duplicate outgoing connections from the fire source room", uniqueConnections.Num(), Elem.Value.Edges.Num());
		}
	}

	// Проверяем, что не осталось связей, направленных к удаленной комнате (Room 2)
	for (auto& Elem : OutgoingConnections)
	{
		for (auto& Edge : Elem.Value.Edges)
		{
			TestFalse("There should be no connections leading to the merged room (Room 2)", Edge.Edge->RoomEndID == 2);
		}
	}

	for (auto& Elem : IncomingConnections)
	{
		for (auto& Edge : Elem.Value.Edges)
		{
			TestFalse("There should be no connections coming from the merged room (Room 2)", Edge.Edge->RoomStartID == 2);
		}
	}

	// Проверка, что у комнаты 3 нет входящих связей из комнаты 2
	bool hasIncomingFromRoom2 = false;
	for (auto& EdgePtr : IncomingConnections[3].Edges)
	{
		if (EdgePtr.Edge->RoomStartID == 2)
		{
			hasIncomingFromRoom2 = true;
			break;
		}
	}
	TestFalse("Room 3 should not have incoming connections from Room 2 after merge", hasIncomingFromRoom2);

	float expectedAvgStrength = 0.225f;
	float actualAvgStrength = 0;
	for (auto& EdgePtr : IncomingConnections[3].Edges)
	{
		if (EdgePtr.Edge->RoomStartID == 1) // Исходящая связь из комнаты 1 (очаг) в комнату 3
		{
			actualAvgStrength = EdgePtr.Edge->ConnectionStrength;
			break;
		}
	}
	TestEqual("Average connection strength from Room 1 to Room 3 should be correct after merge", actualAvgStrength, expectedAvgStrength);

	return true;
}
//   406