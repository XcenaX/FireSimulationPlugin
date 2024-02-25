// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "FireSimulation/Public/FireGridManager.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeFireGridManager() {}
// Cross Module References
	FIRESIMULATION_API UScriptStruct* Z_Construct_UScriptStruct_FGridCell();
	UPackage* Z_Construct_UPackage__Script_FireSimulation();
	ENGINE_API UClass* Z_Construct_UClass_AActor_NoRegister();
	FIRESIMULATION_API UClass* Z_Construct_UClass_UFireGridManager_NoRegister();
	FIRESIMULATION_API UClass* Z_Construct_UClass_UFireGridManager();
	COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
	ENGINE_API UClass* Z_Construct_UClass_UWorld_NoRegister();
// End Cross Module References
class UScriptStruct* FGridCell::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern FIRESIMULATION_API uint32 Get_Z_Construct_UScriptStruct_FGridCell_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FGridCell, Z_Construct_UPackage__Script_FireSimulation(), TEXT("GridCell"), sizeof(FGridCell), Get_Z_Construct_UScriptStruct_FGridCell_Hash());
	}
	return Singleton;
}
template<> FIRESIMULATION_API UScriptStruct* StaticStruct<FGridCell>()
{
	return FGridCell::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FGridCell(FGridCell::StaticStruct, TEXT("/Script/FireSimulation"), TEXT("GridCell"), false, nullptr, nullptr);
static struct FScriptStruct_FireSimulation_StaticRegisterNativesFGridCell
{
	FScriptStruct_FireSimulation_StaticRegisterNativesFGridCell()
	{
		UScriptStruct::DeferCppStructOps<FGridCell>(FName(TEXT("GridCell")));
	}
} ScriptStruct_FireSimulation_StaticRegisterNativesFGridCell;
	struct Z_Construct_UScriptStruct_FGridCell_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_OccupyingActor_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_OccupyingActor;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FGridCell_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/FireGridManager.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FGridCell_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FGridCell>();
	}
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FGridCell_Statics::NewProp_OccupyingActor_MetaData[] = {
		{ "Category", "GridCell" },
		{ "Comment", "// \xd0\xa1\xd1\x81\xd1\x8b\xd0\xbb\xd0\xba\xd0\xb0 \xd0\xbd\xd0\xb0 \xd0\xb0\xd0\xba\xd1\x82\xd0\xbe\xd1\x80\xd0\xb0 \xd0\xb2 \xd1\x8f\xd1\x87\xd0\xb5\xd0\xb9\xd0\xba\xd0\xb5. \xd0\x9c\xd0\xbe\xd0\xb6\xd0\xb5\xd1\x82 \xd0\xb1\xd1\x8b\xd1\x82\xd1\x8c nullptr, \xd0\xb5\xd1\x81\xd0\xbb\xd0\xb8 \xd1\x8f\xd1\x87\xd0\xb5\xd0\xb9\xd0\xba\xd0\xb0 \xd0\xbf\xd1\x83\xd1\x81\xd1\x82\xd0\xb0.\n" },
		{ "ModuleRelativePath", "Public/FireGridManager.h" },
		{ "ToolTip", "\xd0\xa1\xd1\x81\xd1\x8b\xd0\xbb\xd0\xba\xd0\xb0 \xd0\xbd\xd0\xb0 \xd0\xb0\xd0\xba\xd1\x82\xd0\xbe\xd1\x80\xd0\xb0 \xd0\xb2 \xd1\x8f\xd1\x87\xd0\xb5\xd0\xb9\xd0\xba\xd0\xb5. \xd0\x9c\xd0\xbe\xd0\xb6\xd0\xb5\xd1\x82 \xd0\xb1\xd1\x8b\xd1\x82\xd1\x8c nullptr, \xd0\xb5\xd1\x81\xd0\xbb\xd0\xb8 \xd1\x8f\xd1\x87\xd0\xb5\xd0\xb9\xd0\xba\xd0\xb0 \xd0\xbf\xd1\x83\xd1\x81\xd1\x82\xd0\xb0." },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UScriptStruct_FGridCell_Statics::NewProp_OccupyingActor = { "OccupyingActor", nullptr, (EPropertyFlags)0x0010000000020015, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FGridCell, OccupyingActor), Z_Construct_UClass_AActor_NoRegister, METADATA_PARAMS(Z_Construct_UScriptStruct_FGridCell_Statics::NewProp_OccupyingActor_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FGridCell_Statics::NewProp_OccupyingActor_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FGridCell_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FGridCell_Statics::NewProp_OccupyingActor,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FGridCell_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_FireSimulation,
		nullptr,
		&NewStructOps,
		"GridCell",
		sizeof(FGridCell),
		alignof(FGridCell),
		Z_Construct_UScriptStruct_FGridCell_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FGridCell_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FGridCell_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FGridCell_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FGridCell()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FGridCell_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_FireSimulation();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("GridCell"), sizeof(FGridCell), Get_Z_Construct_UScriptStruct_FGridCell_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FGridCell_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FGridCell_Hash() { return 2429330267U; }
	DEFINE_FUNCTION(UFireGridManager::execPopulateGridWithActors)
	{
		P_GET_OBJECT(UWorld,Z_Param_World);
		P_GET_OBJECT(AActor,Z_Param_GridActor);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->PopulateGridWithActors(Z_Param_World,Z_Param_GridActor);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UFireGridManager::execDrawGrid)
	{
		P_GET_UBOOL(Z_Param_bVisible);
		P_GET_OBJECT(UWorld,Z_Param_World);
		P_GET_OBJECT(AActor,Z_Param_GridActor);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->DrawGrid(Z_Param_bVisible,Z_Param_World,Z_Param_GridActor);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UFireGridManager::execInitializeGrid)
	{
		P_GET_PROPERTY(FIntProperty,Z_Param_CubesPerDimension);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->InitializeGrid(Z_Param_CubesPerDimension);
		P_NATIVE_END;
	}
	void UFireGridManager::StaticRegisterNativesUFireGridManager()
	{
		UClass* Class = UFireGridManager::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "DrawGrid", &UFireGridManager::execDrawGrid },
			{ "InitializeGrid", &UFireGridManager::execInitializeGrid },
			{ "PopulateGridWithActors", &UFireGridManager::execPopulateGridWithActors },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_UFireGridManager_DrawGrid_Statics
	{
		struct FireGridManager_eventDrawGrid_Parms
		{
			bool bVisible;
			UWorld* World;
			AActor* GridActor;
		};
		static void NewProp_bVisible_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_bVisible;
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_World;
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_GridActor;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	void Z_Construct_UFunction_UFireGridManager_DrawGrid_Statics::NewProp_bVisible_SetBit(void* Obj)
	{
		((FireGridManager_eventDrawGrid_Parms*)Obj)->bVisible = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UFireGridManager_DrawGrid_Statics::NewProp_bVisible = { "bVisible", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(FireGridManager_eventDrawGrid_Parms), &Z_Construct_UFunction_UFireGridManager_DrawGrid_Statics::NewProp_bVisible_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UFireGridManager_DrawGrid_Statics::NewProp_World = { "World", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FireGridManager_eventDrawGrid_Parms, World), Z_Construct_UClass_UWorld_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UFireGridManager_DrawGrid_Statics::NewProp_GridActor = { "GridActor", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FireGridManager_eventDrawGrid_Parms, GridActor), Z_Construct_UClass_AActor_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UFireGridManager_DrawGrid_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFireGridManager_DrawGrid_Statics::NewProp_bVisible,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFireGridManager_DrawGrid_Statics::NewProp_World,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFireGridManager_DrawGrid_Statics::NewProp_GridActor,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UFireGridManager_DrawGrid_Statics::Function_MetaDataParams[] = {
		{ "Comment", "// \xd0\x92\xd0\xb8\xd0\xb7\xd1\x83\xd0\xb0\xd0\xbb\xd0\xb8\xd0\xb7\xd0\xb0\xd1\x86\xd0\xb8\xd1\x8f \xd1\x81\xd0\xb5\xd1\x82\xd0\xba\xd0\xb8.\n" },
		{ "ModuleRelativePath", "Public/FireGridManager.h" },
		{ "ToolTip", "\xd0\x92\xd0\xb8\xd0\xb7\xd1\x83\xd0\xb0\xd0\xbb\xd0\xb8\xd0\xb7\xd0\xb0\xd1\x86\xd0\xb8\xd1\x8f \xd1\x81\xd0\xb5\xd1\x82\xd0\xba\xd0\xb8." },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UFireGridManager_DrawGrid_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UFireGridManager, nullptr, "DrawGrid", nullptr, nullptr, sizeof(FireGridManager_eventDrawGrid_Parms), Z_Construct_UFunction_UFireGridManager_DrawGrid_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UFireGridManager_DrawGrid_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UFireGridManager_DrawGrid_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UFireGridManager_DrawGrid_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UFireGridManager_DrawGrid()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UFireGridManager_DrawGrid_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UFireGridManager_InitializeGrid_Statics
	{
		struct FireGridManager_eventInitializeGrid_Parms
		{
			int32 CubesPerDimension;
		};
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_CubesPerDimension;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UFireGridManager_InitializeGrid_Statics::NewProp_CubesPerDimension = { "CubesPerDimension", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FireGridManager_eventInitializeGrid_Parms, CubesPerDimension), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UFireGridManager_InitializeGrid_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFireGridManager_InitializeGrid_Statics::NewProp_CubesPerDimension,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UFireGridManager_InitializeGrid_Statics::Function_MetaDataParams[] = {
		{ "Comment", "// \xd0\x98\xd0\xbd\xd0\xb8\xd1\x86\xd0\xb8\xd0\xb0\xd0\xbb\xd0\xb8\xd0\xb7\xd0\xb0\xd1\x86\xd0\xb8\xd1\x8f \xd1\x81\xd0\xb5\xd1\x82\xd0\xba\xd0\xb8 \xd0\xbd\xd0\xb0 \xd0\xbe\xd1\x81\xd0\xbd\xd0\xbe\xd0\xb2\xd0\xb5 \xd0\xba\xd0\xbe\xd0\xbb\xd0\xb8\xd1\x87\xd0\xb5\xd1\x81\xd1\x82\xd0\xb2\xd0\xb0 \xd1\x8d\xd0\xbb\xd0\xb5\xd0\xbc\xd0\xb5\xd0\xbd\xd1\x82\xd0\xbe\xd0\xb2 \xd0\xb2 \xd0\xbe\xd0\xb4\xd0\xbd\xd0\xbe\xd0\xbc \xd0\xb8\xd0\xb7\xd0\xbc\xd0\xb5\xd1\x80\xd0\xb5\xd0\xbd\xd0\xb8\xd0\xb8.\n" },
		{ "ModuleRelativePath", "Public/FireGridManager.h" },
		{ "ToolTip", "\xd0\x98\xd0\xbd\xd0\xb8\xd1\x86\xd0\xb8\xd0\xb0\xd0\xbb\xd0\xb8\xd0\xb7\xd0\xb0\xd1\x86\xd0\xb8\xd1\x8f \xd1\x81\xd0\xb5\xd1\x82\xd0\xba\xd0\xb8 \xd0\xbd\xd0\xb0 \xd0\xbe\xd1\x81\xd0\xbd\xd0\xbe\xd0\xb2\xd0\xb5 \xd0\xba\xd0\xbe\xd0\xbb\xd0\xb8\xd1\x87\xd0\xb5\xd1\x81\xd1\x82\xd0\xb2\xd0\xb0 \xd1\x8d\xd0\xbb\xd0\xb5\xd0\xbc\xd0\xb5\xd0\xbd\xd1\x82\xd0\xbe\xd0\xb2 \xd0\xb2 \xd0\xbe\xd0\xb4\xd0\xbd\xd0\xbe\xd0\xbc \xd0\xb8\xd0\xb7\xd0\xbc\xd0\xb5\xd1\x80\xd0\xb5\xd0\xbd\xd0\xb8\xd0\xb8." },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UFireGridManager_InitializeGrid_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UFireGridManager, nullptr, "InitializeGrid", nullptr, nullptr, sizeof(FireGridManager_eventInitializeGrid_Parms), Z_Construct_UFunction_UFireGridManager_InitializeGrid_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UFireGridManager_InitializeGrid_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UFireGridManager_InitializeGrid_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UFireGridManager_InitializeGrid_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UFireGridManager_InitializeGrid()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UFireGridManager_InitializeGrid_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UFireGridManager_PopulateGridWithActors_Statics
	{
		struct FireGridManager_eventPopulateGridWithActors_Parms
		{
			UWorld* World;
			AActor* GridActor;
		};
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_World;
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_GridActor;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UFireGridManager_PopulateGridWithActors_Statics::NewProp_World = { "World", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FireGridManager_eventPopulateGridWithActors_Parms, World), Z_Construct_UClass_UWorld_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UFireGridManager_PopulateGridWithActors_Statics::NewProp_GridActor = { "GridActor", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FireGridManager_eventPopulateGridWithActors_Parms, GridActor), Z_Construct_UClass_AActor_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UFireGridManager_PopulateGridWithActors_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFireGridManager_PopulateGridWithActors_Statics::NewProp_World,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFireGridManager_PopulateGridWithActors_Statics::NewProp_GridActor,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UFireGridManager_PopulateGridWithActors_Statics::Function_MetaDataParams[] = {
		{ "Comment", "// \xd0\x97\xd0\xb0\xd0\xbf\xd0\xbe\xd0\xbb\xd0\xbd\xd0\xb5\xd0\xbd\xd0\xb8\xd0\xb5 \xd1\x81\xd0\xb5\xd1\x82\xd0\xba\xd0\xb8 \xd0\xb0\xd0\xba\xd1\x82\xd0\xbe\xd1\x80\xd0\xb0\xd0\xbc\xd0\xb8 \xd1\x81 \xd0\xba\xd0\xbe\xd0\xbc\xd0\xbf\xd0\xbe\xd0\xbd\xd0\xb5\xd0\xbd\xd1\x82\xd0\xbe\xd0\xbc FireSimulationComponent.\n" },
		{ "ModuleRelativePath", "Public/FireGridManager.h" },
		{ "ToolTip", "\xd0\x97\xd0\xb0\xd0\xbf\xd0\xbe\xd0\xbb\xd0\xbd\xd0\xb5\xd0\xbd\xd0\xb8\xd0\xb5 \xd1\x81\xd0\xb5\xd1\x82\xd0\xba\xd0\xb8 \xd0\xb0\xd0\xba\xd1\x82\xd0\xbe\xd1\x80\xd0\xb0\xd0\xbc\xd0\xb8 \xd1\x81 \xd0\xba\xd0\xbe\xd0\xbc\xd0\xbf\xd0\xbe\xd0\xbd\xd0\xb5\xd0\xbd\xd1\x82\xd0\xbe\xd0\xbc FireSimulationComponent." },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UFireGridManager_PopulateGridWithActors_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UFireGridManager, nullptr, "PopulateGridWithActors", nullptr, nullptr, sizeof(FireGridManager_eventPopulateGridWithActors_Parms), Z_Construct_UFunction_UFireGridManager_PopulateGridWithActors_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UFireGridManager_PopulateGridWithActors_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UFireGridManager_PopulateGridWithActors_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UFireGridManager_PopulateGridWithActors_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UFireGridManager_PopulateGridWithActors()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UFireGridManager_PopulateGridWithActors_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_UFireGridManager_NoRegister()
	{
		return UFireGridManager::StaticClass();
	}
	struct Z_Construct_UClass_UFireGridManager_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UFireGridManager_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UObject,
		(UObject* (*)())Z_Construct_UPackage__Script_FireSimulation,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_UFireGridManager_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_UFireGridManager_DrawGrid, "DrawGrid" }, // 3560441685
		{ &Z_Construct_UFunction_UFireGridManager_InitializeGrid, "InitializeGrid" }, // 2977590755
		{ &Z_Construct_UFunction_UFireGridManager_PopulateGridWithActors, "PopulateGridWithActors" }, // 4288182840
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFireGridManager_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \xd0\x9a\xd0\xbb\xd0\xb0\xd1\x81\xd1\x81 \xd0\xb4\xd0\xbb\xd1\x8f \xd1\x83\xd0\xbf\xd1\x80\xd0\xb0\xd0\xb2\xd0\xbb\xd0\xb5\xd0\xbd\xd0\xb8\xd1\x8f \xd1\x82\xd1\x80\xd0\xb5\xd1\x85\xd0\xbc\xd0\xb5\xd1\x80\xd0\xbd\xd0\xbe\xd0\xb9 \xd1\x81\xd0\xb5\xd1\x82\xd0\xba\xd0\xbe\xd0\xb9 \xd1\x80\xd0\xb0\xd1\x81\xd0\xbf\xd1\x80\xd0\xbe\xd1\x81\xd1\x82\xd1\x80\xd0\xb0\xd0\xbd\xd0\xb5\xd0\xbd\xd0\xb8\xd1\x8f \xd0\xbe\xd0\xb3\xd0\xbd\xd1\x8f.\n */" },
		{ "IncludePath", "FireGridManager.h" },
		{ "ModuleRelativePath", "Public/FireGridManager.h" },
		{ "ToolTip", "\xd0\x9a\xd0\xbb\xd0\xb0\xd1\x81\xd1\x81 \xd0\xb4\xd0\xbb\xd1\x8f \xd1\x83\xd0\xbf\xd1\x80\xd0\xb0\xd0\xb2\xd0\xbb\xd0\xb5\xd0\xbd\xd0\xb8\xd1\x8f \xd1\x82\xd1\x80\xd0\xb5\xd1\x85\xd0\xbc\xd0\xb5\xd1\x80\xd0\xbd\xd0\xbe\xd0\xb9 \xd1\x81\xd0\xb5\xd1\x82\xd0\xba\xd0\xbe\xd0\xb9 \xd1\x80\xd0\xb0\xd1\x81\xd0\xbf\xd1\x80\xd0\xbe\xd1\x81\xd1\x82\xd1\x80\xd0\xb0\xd0\xbd\xd0\xb5\xd0\xbd\xd0\xb8\xd1\x8f \xd0\xbe\xd0\xb3\xd0\xbd\xd1\x8f." },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UFireGridManager_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UFireGridManager>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UFireGridManager_Statics::ClassParams = {
		&UFireGridManager::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		0,
		0,
		0x001000A0u,
		METADATA_PARAMS(Z_Construct_UClass_UFireGridManager_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UFireGridManager_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UFireGridManager()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UFireGridManager_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UFireGridManager, 593692483);
	template<> FIRESIMULATION_API UClass* StaticClass<UFireGridManager>()
	{
		return UFireGridManager::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UFireGridManager(Z_Construct_UClass_UFireGridManager, &UFireGridManager::StaticClass, TEXT("/Script/FireSimulation"), TEXT("UFireGridManager"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UFireGridManager);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
