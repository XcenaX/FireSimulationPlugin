// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "FireSimulation/Public/MaterialData.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeMaterialData() {}
// Cross Module References
	FIRESIMULATION_API UScriptStruct* Z_Construct_UScriptStruct_FMaterialData();
	UPackage* Z_Construct_UPackage__Script_FireSimulation();
// End Cross Module References
class UScriptStruct* FMaterialData::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern FIRESIMULATION_API uint32 Get_Z_Construct_UScriptStruct_FMaterialData_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FMaterialData, Z_Construct_UPackage__Script_FireSimulation(), TEXT("MaterialData"), sizeof(FMaterialData), Get_Z_Construct_UScriptStruct_FMaterialData_Hash());
	}
	return Singleton;
}
template<> FIRESIMULATION_API UScriptStruct* StaticStruct<FMaterialData>()
{
	return FMaterialData::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FMaterialData(FMaterialData::StaticStruct, TEXT("/Script/FireSimulation"), TEXT("MaterialData"), false, nullptr, nullptr);
static struct FScriptStruct_FireSimulation_StaticRegisterNativesFMaterialData
{
	FScriptStruct_FireSimulation_StaticRegisterNativesFMaterialData()
	{
		UScriptStruct::DeferCppStructOps<FMaterialData>(FName(TEXT("MaterialData")));
	}
} ScriptStruct_FireSimulation_StaticRegisterNativesFMaterialData;
	struct Z_Construct_UScriptStruct_FMaterialData_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Name_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_Name;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_LowestHeatOfCombustion_kJ_per_kg_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_LowestHeatOfCombustion_kJ_per_kg;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_LinearFlameSpeed_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_LinearFlameSpeed;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_BurningRate_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_BurningRate;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_SmokeGeneration_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_SmokeGeneration;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_OxygenConsumption_kg_per_kg_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_OxygenConsumption_kg_per_kg;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_CarbonDioxide_kg_per_kg_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_CarbonDioxide_kg_per_kg;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_CarbonMonoxide_kg_per_kg_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_CarbonMonoxide_kg_per_kg;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_HydrogenChloride_kg_per_kg_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_HydrogenChloride_kg_per_kg;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FMaterialData_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/MaterialData.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FMaterialData_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FMaterialData>();
	}
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FMaterialData_Statics::NewProp_Name_MetaData[] = {
		{ "Category", "Material Data" },
		{ "ModuleRelativePath", "Public/MaterialData.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FMaterialData_Statics::NewProp_Name = { "Name", nullptr, (EPropertyFlags)0x0010000000020015, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FMaterialData, Name), METADATA_PARAMS(Z_Construct_UScriptStruct_FMaterialData_Statics::NewProp_Name_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FMaterialData_Statics::NewProp_Name_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FMaterialData_Statics::NewProp_LowestHeatOfCombustion_kJ_per_kg_MetaData[] = {
		{ "Category", "Material Data" },
		{ "ModuleRelativePath", "Public/MaterialData.h" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FMaterialData_Statics::NewProp_LowestHeatOfCombustion_kJ_per_kg = { "LowestHeatOfCombustion_kJ_per_kg", nullptr, (EPropertyFlags)0x0010000000020015, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FMaterialData, LowestHeatOfCombustion_kJ_per_kg), METADATA_PARAMS(Z_Construct_UScriptStruct_FMaterialData_Statics::NewProp_LowestHeatOfCombustion_kJ_per_kg_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FMaterialData_Statics::NewProp_LowestHeatOfCombustion_kJ_per_kg_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FMaterialData_Statics::NewProp_LinearFlameSpeed_MetaData[] = {
		{ "Category", "Material Data" },
		{ "ModuleRelativePath", "Public/MaterialData.h" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FMaterialData_Statics::NewProp_LinearFlameSpeed = { "LinearFlameSpeed", nullptr, (EPropertyFlags)0x0010000000020015, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FMaterialData, LinearFlameSpeed), METADATA_PARAMS(Z_Construct_UScriptStruct_FMaterialData_Statics::NewProp_LinearFlameSpeed_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FMaterialData_Statics::NewProp_LinearFlameSpeed_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FMaterialData_Statics::NewProp_BurningRate_MetaData[] = {
		{ "Category", "Material Data" },
		{ "ModuleRelativePath", "Public/MaterialData.h" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FMaterialData_Statics::NewProp_BurningRate = { "BurningRate", nullptr, (EPropertyFlags)0x0010000000020015, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FMaterialData, BurningRate), METADATA_PARAMS(Z_Construct_UScriptStruct_FMaterialData_Statics::NewProp_BurningRate_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FMaterialData_Statics::NewProp_BurningRate_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FMaterialData_Statics::NewProp_SmokeGeneration_MetaData[] = {
		{ "Category", "Material Data" },
		{ "ModuleRelativePath", "Public/MaterialData.h" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FMaterialData_Statics::NewProp_SmokeGeneration = { "SmokeGeneration", nullptr, (EPropertyFlags)0x0010000000020015, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FMaterialData, SmokeGeneration), METADATA_PARAMS(Z_Construct_UScriptStruct_FMaterialData_Statics::NewProp_SmokeGeneration_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FMaterialData_Statics::NewProp_SmokeGeneration_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FMaterialData_Statics::NewProp_OxygenConsumption_kg_per_kg_MetaData[] = {
		{ "Category", "Material Data" },
		{ "ModuleRelativePath", "Public/MaterialData.h" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FMaterialData_Statics::NewProp_OxygenConsumption_kg_per_kg = { "OxygenConsumption_kg_per_kg", nullptr, (EPropertyFlags)0x0010000000020015, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FMaterialData, OxygenConsumption_kg_per_kg), METADATA_PARAMS(Z_Construct_UScriptStruct_FMaterialData_Statics::NewProp_OxygenConsumption_kg_per_kg_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FMaterialData_Statics::NewProp_OxygenConsumption_kg_per_kg_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FMaterialData_Statics::NewProp_CarbonDioxide_kg_per_kg_MetaData[] = {
		{ "Category", "Material Data" },
		{ "Comment", "// \xd0\x94\xd0\xb0\xd0\xbd\xd0\xbd\xd1\x8b\xd0\xb5 \xd0\xbe \xd0\xb3\xd0\xb0\xd0\xb7\xd0\xbe\xd0\xb2\xd1\x8b\xd1\x85 \xd1\x8d\xd0\xbc\xd0\xb8\xd1\x81\xd1\x81\xd0\xb8\xd1\x8f\xd1\x85\n" },
		{ "ModuleRelativePath", "Public/MaterialData.h" },
		{ "ToolTip", "\xd0\x94\xd0\xb0\xd0\xbd\xd0\xbd\xd1\x8b\xd0\xb5 \xd0\xbe \xd0\xb3\xd0\xb0\xd0\xb7\xd0\xbe\xd0\xb2\xd1\x8b\xd1\x85 \xd1\x8d\xd0\xbc\xd0\xb8\xd1\x81\xd1\x81\xd0\xb8\xd1\x8f\xd1\x85" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FMaterialData_Statics::NewProp_CarbonDioxide_kg_per_kg = { "CarbonDioxide_kg_per_kg", nullptr, (EPropertyFlags)0x0010000000020015, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FMaterialData, CarbonDioxide_kg_per_kg), METADATA_PARAMS(Z_Construct_UScriptStruct_FMaterialData_Statics::NewProp_CarbonDioxide_kg_per_kg_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FMaterialData_Statics::NewProp_CarbonDioxide_kg_per_kg_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FMaterialData_Statics::NewProp_CarbonMonoxide_kg_per_kg_MetaData[] = {
		{ "Category", "Material Data" },
		{ "ModuleRelativePath", "Public/MaterialData.h" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FMaterialData_Statics::NewProp_CarbonMonoxide_kg_per_kg = { "CarbonMonoxide_kg_per_kg", nullptr, (EPropertyFlags)0x0010000000020015, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FMaterialData, CarbonMonoxide_kg_per_kg), METADATA_PARAMS(Z_Construct_UScriptStruct_FMaterialData_Statics::NewProp_CarbonMonoxide_kg_per_kg_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FMaterialData_Statics::NewProp_CarbonMonoxide_kg_per_kg_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FMaterialData_Statics::NewProp_HydrogenChloride_kg_per_kg_MetaData[] = {
		{ "Category", "Material Data" },
		{ "ModuleRelativePath", "Public/MaterialData.h" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FMaterialData_Statics::NewProp_HydrogenChloride_kg_per_kg = { "HydrogenChloride_kg_per_kg", nullptr, (EPropertyFlags)0x0010000000020015, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FMaterialData, HydrogenChloride_kg_per_kg), METADATA_PARAMS(Z_Construct_UScriptStruct_FMaterialData_Statics::NewProp_HydrogenChloride_kg_per_kg_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FMaterialData_Statics::NewProp_HydrogenChloride_kg_per_kg_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FMaterialData_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FMaterialData_Statics::NewProp_Name,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FMaterialData_Statics::NewProp_LowestHeatOfCombustion_kJ_per_kg,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FMaterialData_Statics::NewProp_LinearFlameSpeed,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FMaterialData_Statics::NewProp_BurningRate,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FMaterialData_Statics::NewProp_SmokeGeneration,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FMaterialData_Statics::NewProp_OxygenConsumption_kg_per_kg,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FMaterialData_Statics::NewProp_CarbonDioxide_kg_per_kg,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FMaterialData_Statics::NewProp_CarbonMonoxide_kg_per_kg,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FMaterialData_Statics::NewProp_HydrogenChloride_kg_per_kg,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FMaterialData_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_FireSimulation,
		nullptr,
		&NewStructOps,
		"MaterialData",
		sizeof(FMaterialData),
		alignof(FMaterialData),
		Z_Construct_UScriptStruct_FMaterialData_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FMaterialData_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FMaterialData_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FMaterialData_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FMaterialData()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FMaterialData_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_FireSimulation();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("MaterialData"), sizeof(FMaterialData), Get_Z_Construct_UScriptStruct_FMaterialData_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FMaterialData_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FMaterialData_Hash() { return 951447981U; }
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
