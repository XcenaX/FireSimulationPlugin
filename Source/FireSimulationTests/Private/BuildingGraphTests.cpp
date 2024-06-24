#include "CoreMinimal.h"
#include "Misc/AutomationTest.h"
#include "BuildingGraph.h"
#include "Misc/FileHelper.h"

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
	FirstRoom->Initialize(1, true, 0.8f, 0.6f, 293.15f, 1.2f, 1000.0f, 50.0f, 50000.0f, 0.5f, 0.01f, 0.5f, nullptr);
	BuildingGraph->AddRoom(FirstRoom);

	TestTrue("First room with fire source should be added", BuildingGraph->GetRooms().Contains(1) && FirstRoom->IsGasSource);

	URoomNode* SecondRoom = NewObject<URoomNode>();
	SecondRoom->Initialize(2, true, 0.8f, 0.6f, 293.15f, 1.2f, 1000.0f, 50.0f, 50000.0f, 0.5f, 0.01f, 0.5f, nullptr);
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
	RoomC->Initialize(3, false, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, nullptr);
	BuildingGraph->AddRoom(RoomC);

	URoomNode* RoomA = NewObject<URoomNode>();
	RoomA->Initialize(1, false, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, nullptr);
	BuildingGraph->AddRoom(RoomA);

	URoomNode* RoomB = NewObject<URoomNode>();
	RoomB->Initialize(2, false, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, nullptr);
	BuildingGraph->AddRoom(RoomB);

	URoomNode* RoomD = NewObject<URoomNode>();
	RoomD->Initialize(4, false, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, nullptr);
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

	TestTrue("RoomD should come after RoomB and RoomC", IndexD > IndexB && IndexD > IndexC);
	TestTrue("RoomB and RoomC should come after RoomA", IndexB > IndexA && IndexC > IndexA);

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FTopologicalSortCycleTest, "FireSimulation.FireSimulationTests.BuildingGraphTests.TopologicalSort.Cycle", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FTopologicalSortCycleTest::RunTest(const FString& Parameters)
{
	UBuildingGraphTestHelper* BuildingGraph = NewObject<UBuildingGraphTestHelper>();

	URoomNode* RoomA = NewObject<URoomNode>();
	RoomA->Initialize(1, false, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, nullptr);
	BuildingGraph->AddRoom(RoomA);

	URoomNode* RoomB = NewObject<URoomNode>();
	RoomB->Initialize(2, false, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, nullptr);
	BuildingGraph->AddRoom(RoomB);

	BuildingGraph->AddConnection(RoomA, RoomB, EConnectionStatus::DoorOpen);
	BuildingGraph->AddConnection(RoomB, RoomA, EConnectionStatus::DoorOpen);

	bool bSortResult = BuildingGraph->TestTopologicalSort();

	TestFalse("Topological sort should fail due to a cycle", bSortResult);

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FMergeRoomsTest, "FireSimulation.FireSimulationTests.BuildingGraphTests.MergeRooms", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FMergeRoomsTest::RunTest(const FString& Parameters)
{
	UBuildingGraphTestHelper* BuildingGraph = NewObject<UBuildingGraphTestHelper>();

	URoomNode* FireSourceRoom = NewObject<URoomNode>();
	FireSourceRoom->Initialize(1, true, 0.8f, 0.6f, 293.15f, 1.2f, 1000.0f, 50.0f, 50000.0f, 0.5f, 0.01f, 0.5f, nullptr);
	BuildingGraph->AddRoom(FireSourceRoom);

	TArray<URoomNode*> rooms;
	for (int i = 2; i <= 6; ++i) {
		URoomNode* Room = NewObject<URoomNode>();
		Room->Initialize(i, false, 0.9f, 0.7f, 295.15f, 1.3f, 1050.0f, 60.0f * i, 55000.0f, 0.6f, 0.02f, 0.6f, nullptr);
		BuildingGraph->AddRoom(Room);
		rooms.Add(Room);
	}

	BuildingGraph->AddConnection(FireSourceRoom, rooms[0], EConnectionStatus::DoorOpen);
	BuildingGraph->AddConnection(rooms[1], rooms[0], EConnectionStatus::DoorOpen);
	BuildingGraph->AddConnection(rooms[1], rooms[2], EConnectionStatus::DoorOpen);
	BuildingGraph->AddConnection(FireSourceRoom, rooms[3], EConnectionStatus::DoorOpen);
	BuildingGraph->AddConnection(rooms[3], rooms[4], EConnectionStatus::DoorOpen);
	BuildingGraph->AddConnection(FireSourceRoom, rooms[1], EConnectionStatus::DoorClosed);

	BuildingGraph->PrepareGraphToWork();

	bool mergeResult = BuildingGraph->MergeToSourceRoom(2);
	TestTrue("Merge should succeed with direct connections from fire source", mergeResult);

	TestFalse("Room 2 should be removed from the graph after merge", BuildingGraph->TestGetRooms().Contains(2));

	URoomNode* UpdatedFireSourceRoom = BuildingGraph->TestGetRooms().FindRef(1);
	float expectedVolumeAfterMerge = 50.0f + 60.0f * 2;
	TestEqual("Updated fire source room volume should be correct after merge", UpdatedFireSourceRoom->RoomVolume, expectedVolumeAfterMerge);

	TMap<int32, FGraphEdgeSet>& OutgoingConnections = BuildingGraph->TestGetOutgoingConnections();
	TMap<int32, FGraphEdgeSet>& IncomingConnections = BuildingGraph->TestGetIncomingConnections();

	for (auto& Elem : OutgoingConnections)
	{
		if (Elem.Key == 1)
		{
			TSet<int32> uniqueConnections;
			for (auto& Edge : Elem.Value.Edges)
			{
				uniqueConnections.Add(Edge.Edge->RoomEndID);
			}
			TestEqual("There should be no duplicate outgoing connections from the fire source room", uniqueConnections.Num(), Elem.Value.Edges.Num());
		}
	}

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
		if (EdgePtr.Edge->RoomStartID == 1)
		{
			actualAvgStrength = EdgePtr.Edge->ConnectionStrength;
			break;
		}
	}
	TestEqual("Average connection strength from Room 1 to Room 3 should be correct after merge", actualAvgStrength, expectedAvgStrength);

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FFireSimulationTest, "FireSimulation.FireSimulationTests.BuildingGraphTests.FireSimulation", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FFireSimulationTest::RunTest(const FString& Parameters)
{
	UBuildingGraphTestHelper* BuildingGraph = NewObject<UBuildingGraphTestHelper>();

	URoomNode* FireSourceRoom = NewObject<URoomNode>(); // 1
	FireSourceRoom->Initialize(1, true, 0.8f, 0.6f, 293.15f, 1.2f, 1000.0f, 50.0f, 50000.0f, 0.5f, 0.01f, 0.5f, nullptr);
	BuildingGraph->AddRoom(FireSourceRoom);

	URoomNode* FireRoom1 = NewObject<URoomNode>(); // 1
	FireRoom1->Initialize(1, false, 0.8f, 0.6f, 293.15f, 1.2f, 1000.0f, 50.0f, 50000.0f, 0.5f, 0.01f, 0.5f, nullptr);
	BuildingGraph->AddRoom(FireRoom1);

	URoomNode* FireRoom2 = NewObject<URoomNode>(); // 2
	FireRoom2->Initialize(2, false, 0.8f, 0.6f, 293.15f, 1.2f, 1000.0f, 50.0f, 50000.0f, 0.5f, 0.01f, 0.5f, nullptr);
	BuildingGraph->AddRoom(FireRoom2);

	URoomNode* FireRoom3 = NewObject<URoomNode>(); // 3
	FireRoom3->Initialize(3, false, 0.8f, 0.6f, 293.15f, 1.2f, 1000.0f, 50.0f, 50000.0f, 0.5f, 0.01f, 0.5f, nullptr);
	BuildingGraph->AddRoom(FireRoom3);

	URoomNode* FireRoom5 = NewObject<URoomNode>(); // 5
	FireRoom5->Initialize(5, false, 0.8f, 0.6f, 293.15f, 1.2f, 1000.0f, 50.0f, 50000.0f, 0.5f, 0.01f, 0.5f, nullptr);
	BuildingGraph->AddRoom(FireRoom5);

	BuildingGraph->AddConnection(FireRoom5, FireRoom2, EConnectionStatus::DoorOpen);
	BuildingGraph->AddConnection(FireRoom5, FireRoom1, EConnectionStatus::DoorOpen);
	BuildingGraph->AddConnection(FireSourceRoom, FireRoom5, EConnectionStatus::DoorOpen);
	BuildingGraph->AddConnection(FireRoom5, FireRoom3, EConnectionStatus::DoorClosed);

	BuildingGraph->PrepareGraphToWork();

	for (int32 i = 0; i < 500; i++) {
		BuildingGraph->CalculateFireDynamicsForSecond(i);
	}

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FVKRTest, "FireSimulation.FireSimulationTests.BuildingGraphTests.VKR", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FVKRTest::RunTest(const FString& Parameters)
{
	FString FilePath = FPaths::ProjectDir() / TEXT("VisibilityData.txt");
	FString DataToSave;

	UBuildingGraphTestHelper* BuildingGraph = NewObject<UBuildingGraphTestHelper>();

	URoomNode* FireSourceRoom = NewObject<URoomNode>(); // 1
	//FireSourceRoom->Initialize(1, true, 0.87f, 0.95f, 293.0f, 1.21f, 1.03f, 300.0f, 14094.12f, 0.012f, 0.015f, 611.0f, nullptr);
	FireSourceRoom->Initialize(1, true, 0.87f, 0.95f, 293.0f, 1.21f, 1.03f, 500.0f, 13800.0f, 0.0108f, 0.0145f, 270.0f, nullptr);
	BuildingGraph->AddRoom(FireSourceRoom);

	URoomNode* FireRoom2 = NewObject<URoomNode>(); // 2
	//FireRoom2->Initialize(2, false, 0.87f, 0.95f, 293.0f, 1.21f, 1.03f, 300.0f, 14093.71f, 0.014f, 0.015f, 412.60f, nullptr);
	FireRoom2->Initialize(2, false, 0.87f, 0.95f, 293.0f, 1.21f, 1.03f, 250.0f, 13800.0f, 0.0108f, 0.0145f, 270.0f, nullptr);
	BuildingGraph->AddRoom(FireRoom2);

	URoomNode* FireRoom3 = NewObject<URoomNode>(); // 3
	//FireRoom3->Initialize(3, false, 0.87f, 0.95f, 293.0f, 1.21f, 1.03f, 300.0f, 14093.71f, 0.014f, 0.015f, 412.60f, nullptr);
	FireRoom3->Initialize(3, false, 0.87f, 0.95f, 293.0f, 1.21f, 1.03f, 250.0f, 13800.0f, 0.0108f, 0.0145f, 270.0f, nullptr);
	BuildingGraph->AddRoom(FireRoom3);

	URoomNode* FireRoom4 = NewObject<URoomNode>(); // 4
	//FireRoom4->Initialize(4, false, 0.87f, 0.95f, 293.0f, 1.21f, 1.03f, 300.0f, 14093.71f, 0.014f, 0.015f, 412.60f, nullptr);
	FireRoom4->Initialize(4, false, 0.87f, 0.95f, 293.0f, 1.21f, 1.03f, 500.0f, 13800.0f, 0.0108f, 0.0145f, 270.0f, nullptr);
	BuildingGraph->AddRoom(FireRoom4);

	BuildingGraph->AddConnection(FireSourceRoom, FireRoom2, EConnectionStatus::DoorOpen);
	BuildingGraph->AddConnection(FireSourceRoom, FireRoom3, EConnectionStatus::DoorOpen);
	BuildingGraph->AddConnection(FireRoom2, FireRoom4, EConnectionStatus::DoorOpen);
	BuildingGraph->AddConnection(FireRoom3, FireRoom4, EConnectionStatus::DoorOpen);

	BuildingGraph->PrepareGraphToWork();

	DataToSave += FString::Printf(TEXT("Second;Room1;Room2;Room3;\n"));

	for (int32 i = 0; i < 1500; i++) {
		if (i == 200)
		{
			//BuildingGraph->MergeToSourceRoom(2);
			//auto stop = BuildingGraph->GetRooms()[1]->heat_of_combustion_;
		}
		/*if (i == 500)
		{
			UGraphEdge* OutgoingEdge = nullptr;
			for (UGraphEdge* Edge : BuildingGraph->GetOutgoingConnections().Find(1)->Edges)
			{
				if (Edge && Edge->RoomStartID == FireSourceRoom->RoomID && Edge->RoomEndID == FireRoom2->RoomID)
					OutgoingEdge = Edge;
			}

			UGraphEdge* IncomingEdge = nullptr;
			for (UGraphEdge* Edge : BuildingGraph->GetIncomingConnections().Find(FireRoom2->RoomID)->Edges)
			{
				if (Edge && Edge->RoomStartID == FireSourceRoom->RoomID && Edge->RoomEndID == FireRoom2->RoomID)
					IncomingEdge = Edge;
			}

			OutgoingEdge->SetConnectionStrengthFromStatus(EConnectionStatus::DoorClosed);
			IncomingEdge->SetConnectionStrengthFromStatus(EConnectionStatus::DoorClosed);

			URoomNode* Room = BuildingGraph->GetRooms()[FireRoom2->RoomID];
			Room->MakeImprint(500, FireSourceRoom->RoomID, EConnectionStatus::DoorOpen);
		}
		if (i == 600)
		{
			UGraphEdge* OutgoingEdge = nullptr;
			for (UGraphEdge* Edge : BuildingGraph->GetOutgoingConnections().Find(1)->Edges)
			{
				if (Edge && Edge->RoomStartID == FireSourceRoom->RoomID && Edge->RoomEndID == FireRoom2->RoomID)
					OutgoingEdge = Edge;
			}

			UGraphEdge* IncomingEdge = nullptr;
			for (UGraphEdge* Edge : BuildingGraph->GetIncomingConnections().Find(FireRoom2->RoomID)->Edges)
			{
				if (Edge && Edge->RoomStartID == FireSourceRoom->RoomID && Edge->RoomEndID == FireRoom2->RoomID)
					IncomingEdge = Edge;
			}

			OutgoingEdge->SetConnectionStrengthFromStatus(EConnectionStatus::DoorOpen);
			IncomingEdge->SetConnectionStrengthFromStatus(EConnectionStatus::DoorOpen);

			URoomNode* Room = BuildingGraph->GetRooms()[FireRoom2->RoomID];
			Room->MakeImprint(600, FireSourceRoom->RoomID, EConnectionStatus::DoorClosed);
		}
		if (i == 800)
		{
			UGraphEdge* OutgoingEdge = nullptr;
			for (UGraphEdge* Edge : BuildingGraph->GetOutgoingConnections().Find(1)->Edges)
			{
				if (Edge && Edge->RoomStartID == FireSourceRoom->RoomID && Edge->RoomEndID == FireRoom2->RoomID)
					OutgoingEdge = Edge;
			}

			UGraphEdge* IncomingEdge = nullptr;
			for (UGraphEdge* Edge : BuildingGraph->GetIncomingConnections().Find(FireRoom2->RoomID)->Edges)
			{
				if (Edge && Edge->RoomStartID == FireSourceRoom->RoomID && Edge->RoomEndID == FireRoom2->RoomID)
					IncomingEdge = Edge;
			}

			OutgoingEdge->SetConnectionStrengthFromStatus(EConnectionStatus::DoorClosed);
			IncomingEdge->SetConnectionStrengthFromStatus(EConnectionStatus::DoorClosed);

			URoomNode* Room = BuildingGraph->GetRooms()[FireRoom2->RoomID];
			Room->MakeImprint(800, FireSourceRoom->RoomID, EConnectionStatus::DoorOpen);
		}
		if (i == 900)
		{
			UGraphEdge* OutgoingEdge = nullptr;
			for (UGraphEdge* Edge : BuildingGraph->GetOutgoingConnections().Find(1)->Edges)
			{
				if (Edge && Edge->RoomStartID == FireSourceRoom->RoomID && Edge->RoomEndID == FireRoom2->RoomID)
					OutgoingEdge = Edge;
			}

			UGraphEdge* IncomingEdge = nullptr;
			for (UGraphEdge* Edge : BuildingGraph->GetIncomingConnections().Find(FireRoom2->RoomID)->Edges)
			{
				if (Edge && Edge->RoomStartID == FireSourceRoom->RoomID && Edge->RoomEndID == FireRoom2->RoomID)
					IncomingEdge = Edge;
			}

			OutgoingEdge->SetConnectionStrengthFromStatus(EConnectionStatus::DoorOpen);
			IncomingEdge->SetConnectionStrengthFromStatus(EConnectionStatus::DoorOpen);

			URoomNode* Room = BuildingGraph->GetRooms()[FireRoom2->RoomID];
			Room->MakeImprint(900, FireSourceRoom->RoomID, EConnectionStatus::DoorClosed);
		}*/
		BuildingGraph->CalculateFireDynamicsForSecond(i);
		DataToSave += FString::Printf(TEXT("%d;"), i);

		for (const auto& RoomPair : BuildingGraph->GetRooms()) {
			URoomNode* Room = RoomPair.Value;
			FFireDynamicsParameters CurrentParams = Room->GetFireDynamics();

			DataToSave += FString::Printf(TEXT("%f;"), CurrentParams.GasTemperature);
			//DataToSave += FString::Printf(TEXT("%f;"), CurrentParams.Visibility);
		}
		DataToSave += FString::Printf(TEXT("\n"));
	}

	FFileHelper::SaveStringToFile(DataToSave, *FilePath);

	return true;
}