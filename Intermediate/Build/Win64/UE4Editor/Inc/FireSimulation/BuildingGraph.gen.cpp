// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "FireSimulation/Public/BuildingGraph.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeBuildingGraph() {}
// Cross Module References
	FIRESIMULATION_API UEnum* Z_Construct_UEnum_FireSimulation_EDoorStatus();
	UPackage* Z_Construct_UPackage__Script_FireSimulation();
	FIRESIMULATION_API UScriptStruct* Z_Construct_UScriptStruct_FDoorEdge();
	FIRESIMULATION_API UScriptStruct* Z_Construct_UScriptStruct_FRoomNode();
	FIRESIMULATION_API UClass* Z_Construct_UClass_UBuildingGraph_NoRegister();
	FIRESIMULATION_API UClass* Z_Construct_UClass_UBuildingGraph();
	COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
// End Cross Module References
	static UEnum* EDoorStatus_StaticEnum()
	{
		static UEnum* Singleton = nullptr;
		if (!Singleton)
		{
			Singleton = GetStaticEnum(Z_Construct_UEnum_FireSimulation_EDoorStatus, Z_Construct_UPackage__Script_FireSimulation(), TEXT("EDoorStatus"));
		}
		return Singleton;
	}
	template<> FIRESIMULATION_API UEnum* StaticEnum<EDoorStatus>()
	{
		return EDoorStatus_StaticEnum();
	}
	static FCompiledInDeferEnum Z_CompiledInDeferEnum_UEnum_EDoorStatus(EDoorStatus_StaticEnum, TEXT("/Script/FireSimulation"), TEXT("EDoorStatus"), false, nullptr, nullptr);
	uint32 Get_Z_Construct_UEnum_FireSimulation_EDoorStatus_Hash() { return 2254309328U; }
	UEnum* Z_Construct_UEnum_FireSimulation_EDoorStatus()
	{
#if WITH_HOT_RELOAD
		UPackage* Outer = Z_Construct_UPackage__Script_FireSimulation();
		static UEnum* ReturnEnum = FindExistingEnumIfHotReloadOrDynamic(Outer, TEXT("EDoorStatus"), 0, Get_Z_Construct_UEnum_FireSimulation_EDoorStatus_Hash(), false);
#else
		static UEnum* ReturnEnum = nullptr;
#endif // WITH_HOT_RELOAD
		if (!ReturnEnum)
		{
			static const UE4CodeGen_Private::FEnumeratorParam Enumerators[] = {
				{ "EDoorStatus::Closed", (int64)EDoorStatus::Closed },
				{ "EDoorStatus::Open", (int64)EDoorStatus::Open },
				{ "EDoorStatus::NoDoor", (int64)EDoorStatus::NoDoor },
			};
#if WITH_METADATA
			const UE4CodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
				{ "BlueprintType", "true" },
				{ "Closed.DisplayName", "Closed" },
				{ "Closed.Name", "EDoorStatus::Closed" },
				{ "ModuleRelativePath", "Public/BuildingGraph.h" },
				{ "NoDoor.DisplayName", "No Door" },
				{ "NoDoor.Name", "EDoorStatus::NoDoor" },
				{ "Open.DisplayName", "Open" },
				{ "Open.Name", "EDoorStatus::Open" },
			};
#endif
			static const UE4CodeGen_Private::FEnumParams EnumParams = {
				(UObject*(*)())Z_Construct_UPackage__Script_FireSimulation,
				nullptr,
				"EDoorStatus",
				"EDoorStatus",
				Enumerators,
				UE_ARRAY_COUNT(Enumerators),
				RF_Public|RF_Transient|RF_MarkAsNative,
				EEnumFlags::None,
				UE4CodeGen_Private::EDynamicType::NotDynamic,
				(uint8)UEnum::ECppForm::EnumClass,
				METADATA_PARAMS(Enum_MetaDataParams, UE_ARRAY_COUNT(Enum_MetaDataParams))
			};
			UE4CodeGen_Private::ConstructUEnum(ReturnEnum, EnumParams);
		}
		return ReturnEnum;
	}
class UScriptStruct* FDoorEdge::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern FIRESIMULATION_API uint32 Get_Z_Construct_UScriptStruct_FDoorEdge_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FDoorEdge, Z_Construct_UPackage__Script_FireSimulation(), TEXT("DoorEdge"), sizeof(FDoorEdge), Get_Z_Construct_UScriptStruct_FDoorEdge_Hash());
	}
	return Singleton;
}
template<> FIRESIMULATION_API UScriptStruct* StaticStruct<FDoorEdge>()
{
	return FDoorEdge::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FDoorEdge(FDoorEdge::StaticStruct, TEXT("/Script/FireSimulation"), TEXT("DoorEdge"), false, nullptr, nullptr);
static struct FScriptStruct_FireSimulation_StaticRegisterNativesFDoorEdge
{
	FScriptStruct_FireSimulation_StaticRegisterNativesFDoorEdge()
	{
		UScriptStruct::DeferCppStructOps<FDoorEdge>(FName(TEXT("DoorEdge")));
	}
} ScriptStruct_FireSimulation_StaticRegisterNativesFDoorEdge;
	struct Z_Construct_UScriptStruct_FDoorEdge_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_RoomAID_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_RoomAID;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_RoomBID_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_RoomBID;
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_DoorStatus_Underlying;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_DoorStatus_MetaData[];
#endif
		static const UE4CodeGen_Private::FEnumPropertyParams NewProp_DoorStatus;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FDoorEdge_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/BuildingGraph.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FDoorEdge_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FDoorEdge>();
	}
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FDoorEdge_Statics::NewProp_RoomAID_MetaData[] = {
		{ "Category", "Door" },
		{ "ModuleRelativePath", "Public/BuildingGraph.h" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FDoorEdge_Statics::NewProp_RoomAID = { "RoomAID", nullptr, (EPropertyFlags)0x0010000000020015, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FDoorEdge, RoomAID), METADATA_PARAMS(Z_Construct_UScriptStruct_FDoorEdge_Statics::NewProp_RoomAID_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FDoorEdge_Statics::NewProp_RoomAID_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FDoorEdge_Statics::NewProp_RoomBID_MetaData[] = {
		{ "Category", "Door" },
		{ "ModuleRelativePath", "Public/BuildingGraph.h" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FDoorEdge_Statics::NewProp_RoomBID = { "RoomBID", nullptr, (EPropertyFlags)0x0010000000020015, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FDoorEdge, RoomBID), METADATA_PARAMS(Z_Construct_UScriptStruct_FDoorEdge_Statics::NewProp_RoomBID_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FDoorEdge_Statics::NewProp_RoomBID_MetaData)) };
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UScriptStruct_FDoorEdge_Statics::NewProp_DoorStatus_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FDoorEdge_Statics::NewProp_DoorStatus_MetaData[] = {
		{ "Category", "Door" },
		{ "ModuleRelativePath", "Public/BuildingGraph.h" },
	};
#endif
	const UE4CodeGen_Private::FEnumPropertyParams Z_Construct_UScriptStruct_FDoorEdge_Statics::NewProp_DoorStatus = { "DoorStatus", nullptr, (EPropertyFlags)0x0010000000020015, UE4CodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FDoorEdge, DoorStatus), Z_Construct_UEnum_FireSimulation_EDoorStatus, METADATA_PARAMS(Z_Construct_UScriptStruct_FDoorEdge_Statics::NewProp_DoorStatus_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FDoorEdge_Statics::NewProp_DoorStatus_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FDoorEdge_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FDoorEdge_Statics::NewProp_RoomAID,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FDoorEdge_Statics::NewProp_RoomBID,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FDoorEdge_Statics::NewProp_DoorStatus_Underlying,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FDoorEdge_Statics::NewProp_DoorStatus,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FDoorEdge_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_FireSimulation,
		nullptr,
		&NewStructOps,
		"DoorEdge",
		sizeof(FDoorEdge),
		alignof(FDoorEdge),
		Z_Construct_UScriptStruct_FDoorEdge_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FDoorEdge_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FDoorEdge_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FDoorEdge_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FDoorEdge()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FDoorEdge_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_FireSimulation();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("DoorEdge"), sizeof(FDoorEdge), Get_Z_Construct_UScriptStruct_FDoorEdge_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FDoorEdge_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FDoorEdge_Hash() { return 1049240981U; }
class UScriptStruct* FRoomNode::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern FIRESIMULATION_API uint32 Get_Z_Construct_UScriptStruct_FRoomNode_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FRoomNode, Z_Construct_UPackage__Script_FireSimulation(), TEXT("RoomNode"), sizeof(FRoomNode), Get_Z_Construct_UScriptStruct_FRoomNode_Hash());
	}
	return Singleton;
}
template<> FIRESIMULATION_API UScriptStruct* StaticStruct<FRoomNode>()
{
	return FRoomNode::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FRoomNode(FRoomNode::StaticStruct, TEXT("/Script/FireSimulation"), TEXT("RoomNode"), false, nullptr, nullptr);
static struct FScriptStruct_FireSimulation_StaticRegisterNativesFRoomNode
{
	FScriptStruct_FireSimulation_StaticRegisterNativesFRoomNode()
	{
		UScriptStruct::DeferCppStructOps<FRoomNode>(FName(TEXT("RoomNode")));
	}
} ScriptStruct_FireSimulation_StaticRegisterNativesFRoomNode;
	struct Z_Construct_UScriptStruct_FRoomNode_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_RoomID_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_RoomID;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Area_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_Area;
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_Neighbors_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Neighbors_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_Neighbors;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FRoomNode_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/BuildingGraph.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FRoomNode_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FRoomNode>();
	}
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FRoomNode_Statics::NewProp_RoomID_MetaData[] = {
		{ "Category", "Room" },
		{ "ModuleRelativePath", "Public/BuildingGraph.h" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FRoomNode_Statics::NewProp_RoomID = { "RoomID", nullptr, (EPropertyFlags)0x0010000000020015, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FRoomNode, RoomID), METADATA_PARAMS(Z_Construct_UScriptStruct_FRoomNode_Statics::NewProp_RoomID_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FRoomNode_Statics::NewProp_RoomID_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FRoomNode_Statics::NewProp_Area_MetaData[] = {
		{ "Category", "Room" },
		{ "ModuleRelativePath", "Public/BuildingGraph.h" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FRoomNode_Statics::NewProp_Area = { "Area", nullptr, (EPropertyFlags)0x0010000000020015, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FRoomNode, Area), METADATA_PARAMS(Z_Construct_UScriptStruct_FRoomNode_Statics::NewProp_Area_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FRoomNode_Statics::NewProp_Area_MetaData)) };
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FRoomNode_Statics::NewProp_Neighbors_Inner = { "Neighbors", nullptr, (EPropertyFlags)0x0000000000020000, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FRoomNode_Statics::NewProp_Neighbors_MetaData[] = {
		{ "Category", "Room" },
		{ "ModuleRelativePath", "Public/BuildingGraph.h" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FRoomNode_Statics::NewProp_Neighbors = { "Neighbors", nullptr, (EPropertyFlags)0x0010000000020015, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FRoomNode, Neighbors), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UScriptStruct_FRoomNode_Statics::NewProp_Neighbors_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FRoomNode_Statics::NewProp_Neighbors_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FRoomNode_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FRoomNode_Statics::NewProp_RoomID,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FRoomNode_Statics::NewProp_Area,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FRoomNode_Statics::NewProp_Neighbors_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FRoomNode_Statics::NewProp_Neighbors,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FRoomNode_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_FireSimulation,
		nullptr,
		&NewStructOps,
		"RoomNode",
		sizeof(FRoomNode),
		alignof(FRoomNode),
		Z_Construct_UScriptStruct_FRoomNode_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FRoomNode_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FRoomNode_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FRoomNode_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FRoomNode()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FRoomNode_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_FireSimulation();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("RoomNode"), sizeof(FRoomNode), Get_Z_Construct_UScriptStruct_FRoomNode_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FRoomNode_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FRoomNode_Hash() { return 2001827495U; }
	DEFINE_FUNCTION(UBuildingGraph::execCalculateRoomAreas)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->CalculateRoomAreas();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UBuildingGraph::execAddDoor)
	{
		P_GET_STRUCT_REF(FDoorEdge,Z_Param_Out_Door);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->AddDoor(Z_Param_Out_Door);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UBuildingGraph::execAddRoom)
	{
		P_GET_STRUCT_REF(FRoomNode,Z_Param_Out_Room);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->AddRoom(Z_Param_Out_Room);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UBuildingGraph::execInitializeGraph)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->InitializeGraph();
		P_NATIVE_END;
	}
	void UBuildingGraph::StaticRegisterNativesUBuildingGraph()
	{
		UClass* Class = UBuildingGraph::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "AddDoor", &UBuildingGraph::execAddDoor },
			{ "AddRoom", &UBuildingGraph::execAddRoom },
			{ "CalculateRoomAreas", &UBuildingGraph::execCalculateRoomAreas },
			{ "InitializeGraph", &UBuildingGraph::execInitializeGraph },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_UBuildingGraph_AddDoor_Statics
	{
		struct BuildingGraph_eventAddDoor_Parms
		{
			FDoorEdge Door;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Door_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Door;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UBuildingGraph_AddDoor_Statics::NewProp_Door_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UBuildingGraph_AddDoor_Statics::NewProp_Door = { "Door", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(BuildingGraph_eventAddDoor_Parms, Door), Z_Construct_UScriptStruct_FDoorEdge, METADATA_PARAMS(Z_Construct_UFunction_UBuildingGraph_AddDoor_Statics::NewProp_Door_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UBuildingGraph_AddDoor_Statics::NewProp_Door_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UBuildingGraph_AddDoor_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBuildingGraph_AddDoor_Statics::NewProp_Door,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UBuildingGraph_AddDoor_Statics::Function_MetaDataParams[] = {
		{ "Category", "Building Graph" },
		{ "ModuleRelativePath", "Public/BuildingGraph.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UBuildingGraph_AddDoor_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UBuildingGraph, nullptr, "AddDoor", nullptr, nullptr, sizeof(BuildingGraph_eventAddDoor_Parms), Z_Construct_UFunction_UBuildingGraph_AddDoor_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UBuildingGraph_AddDoor_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04420401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UBuildingGraph_AddDoor_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UBuildingGraph_AddDoor_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UBuildingGraph_AddDoor()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UBuildingGraph_AddDoor_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UBuildingGraph_AddRoom_Statics
	{
		struct BuildingGraph_eventAddRoom_Parms
		{
			FRoomNode Room;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Room_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Room;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UBuildingGraph_AddRoom_Statics::NewProp_Room_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UBuildingGraph_AddRoom_Statics::NewProp_Room = { "Room", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(BuildingGraph_eventAddRoom_Parms, Room), Z_Construct_UScriptStruct_FRoomNode, METADATA_PARAMS(Z_Construct_UFunction_UBuildingGraph_AddRoom_Statics::NewProp_Room_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UBuildingGraph_AddRoom_Statics::NewProp_Room_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UBuildingGraph_AddRoom_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBuildingGraph_AddRoom_Statics::NewProp_Room,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UBuildingGraph_AddRoom_Statics::Function_MetaDataParams[] = {
		{ "Category", "Building Graph" },
		{ "ModuleRelativePath", "Public/BuildingGraph.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UBuildingGraph_AddRoom_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UBuildingGraph, nullptr, "AddRoom", nullptr, nullptr, sizeof(BuildingGraph_eventAddRoom_Parms), Z_Construct_UFunction_UBuildingGraph_AddRoom_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UBuildingGraph_AddRoom_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04420401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UBuildingGraph_AddRoom_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UBuildingGraph_AddRoom_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UBuildingGraph_AddRoom()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UBuildingGraph_AddRoom_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UBuildingGraph_CalculateRoomAreas_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UBuildingGraph_CalculateRoomAreas_Statics::Function_MetaDataParams[] = {
		{ "Category", "Building Graph" },
		{ "ModuleRelativePath", "Public/BuildingGraph.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UBuildingGraph_CalculateRoomAreas_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UBuildingGraph, nullptr, "CalculateRoomAreas", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UBuildingGraph_CalculateRoomAreas_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UBuildingGraph_CalculateRoomAreas_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UBuildingGraph_CalculateRoomAreas()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UBuildingGraph_CalculateRoomAreas_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UBuildingGraph_InitializeGraph_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UBuildingGraph_InitializeGraph_Statics::Function_MetaDataParams[] = {
		{ "Category", "Building Graph" },
		{ "ModuleRelativePath", "Public/BuildingGraph.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UBuildingGraph_InitializeGraph_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UBuildingGraph, nullptr, "InitializeGraph", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UBuildingGraph_InitializeGraph_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UBuildingGraph_InitializeGraph_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UBuildingGraph_InitializeGraph()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UBuildingGraph_InitializeGraph_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_UBuildingGraph_NoRegister()
	{
		return UBuildingGraph::StaticClass();
	}
	struct Z_Construct_UClass_UBuildingGraph_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Rooms_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Rooms_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_Rooms;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Doors_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Doors_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_Doors;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UBuildingGraph_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UObject,
		(UObject* (*)())Z_Construct_UPackage__Script_FireSimulation,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_UBuildingGraph_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_UBuildingGraph_AddDoor, "AddDoor" }, // 1400563186
		{ &Z_Construct_UFunction_UBuildingGraph_AddRoom, "AddRoom" }, // 3112931125
		{ &Z_Construct_UFunction_UBuildingGraph_CalculateRoomAreas, "CalculateRoomAreas" }, // 412099464
		{ &Z_Construct_UFunction_UBuildingGraph_InitializeGraph, "InitializeGraph" }, // 3559208274
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UBuildingGraph_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "BuildingGraph.h" },
		{ "ModuleRelativePath", "Public/BuildingGraph.h" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UClass_UBuildingGraph_Statics::NewProp_Rooms_Inner = { "Rooms", nullptr, (EPropertyFlags)0x0000000000020000, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FRoomNode, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UBuildingGraph_Statics::NewProp_Rooms_MetaData[] = {
		{ "Category", "Building Graph" },
		{ "ModuleRelativePath", "Public/BuildingGraph.h" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UClass_UBuildingGraph_Statics::NewProp_Rooms = { "Rooms", nullptr, (EPropertyFlags)0x0020080000020001, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UBuildingGraph, Rooms), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UClass_UBuildingGraph_Statics::NewProp_Rooms_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UBuildingGraph_Statics::NewProp_Rooms_MetaData)) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UClass_UBuildingGraph_Statics::NewProp_Doors_Inner = { "Doors", nullptr, (EPropertyFlags)0x0000000000020000, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FDoorEdge, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UBuildingGraph_Statics::NewProp_Doors_MetaData[] = {
		{ "Category", "Building Graph" },
		{ "ModuleRelativePath", "Public/BuildingGraph.h" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UClass_UBuildingGraph_Statics::NewProp_Doors = { "Doors", nullptr, (EPropertyFlags)0x0020080000020001, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UBuildingGraph, Doors), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UClass_UBuildingGraph_Statics::NewProp_Doors_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UBuildingGraph_Statics::NewProp_Doors_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UBuildingGraph_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBuildingGraph_Statics::NewProp_Rooms_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBuildingGraph_Statics::NewProp_Rooms,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBuildingGraph_Statics::NewProp_Doors_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBuildingGraph_Statics::NewProp_Doors,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UBuildingGraph_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UBuildingGraph>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UBuildingGraph_Statics::ClassParams = {
		&UBuildingGraph::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_UBuildingGraph_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_UBuildingGraph_Statics::PropPointers),
		0,
		0x000000A0u,
		METADATA_PARAMS(Z_Construct_UClass_UBuildingGraph_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UBuildingGraph_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UBuildingGraph()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UBuildingGraph_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UBuildingGraph, 2875071594);
	template<> FIRESIMULATION_API UClass* StaticClass<UBuildingGraph>()
	{
		return UBuildingGraph::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UBuildingGraph(Z_Construct_UClass_UBuildingGraph, &UBuildingGraph::StaticClass, TEXT("/Script/FireSimulation"), TEXT("UBuildingGraph"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UBuildingGraph);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
