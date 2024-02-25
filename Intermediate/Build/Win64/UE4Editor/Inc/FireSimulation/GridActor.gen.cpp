// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "FireSimulation/Public/GridActor.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeGridActor() {}
// Cross Module References
	FIRESIMULATION_API UClass* Z_Construct_UClass_AGridActor_NoRegister();
	FIRESIMULATION_API UClass* Z_Construct_UClass_AGridActor();
	ENGINE_API UClass* Z_Construct_UClass_AActor();
	UPackage* Z_Construct_UPackage__Script_FireSimulation();
	ENGINE_API UClass* Z_Construct_UClass_UBoxComponent_NoRegister();
// End Cross Module References
	void AGridActor::StaticRegisterNativesAGridActor()
	{
	}
	UClass* Z_Construct_UClass_AGridActor_NoRegister()
	{
		return AGridActor::StaticClass();
	}
	struct Z_Construct_UClass_AGridActor_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_GridBounds_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_GridBounds;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AGridActor_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AActor,
		(UObject* (*)())Z_Construct_UPackage__Script_FireSimulation,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AGridActor_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "GridActor.h" },
		{ "ModuleRelativePath", "Public/GridActor.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AGridActor_Statics::NewProp_GridBounds_MetaData[] = {
		{ "Category", "Grid" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/GridActor.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AGridActor_Statics::NewProp_GridBounds = { "GridBounds", nullptr, (EPropertyFlags)0x00100000000a001d, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AGridActor, GridBounds), Z_Construct_UClass_UBoxComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_AGridActor_Statics::NewProp_GridBounds_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AGridActor_Statics::NewProp_GridBounds_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AGridActor_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AGridActor_Statics::NewProp_GridBounds,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_AGridActor_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AGridActor>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_AGridActor_Statics::ClassParams = {
		&AGridActor::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_AGridActor_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_AGridActor_Statics::PropPointers),
		0,
		0x009000A4u,
		METADATA_PARAMS(Z_Construct_UClass_AGridActor_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_AGridActor_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AGridActor()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_AGridActor_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(AGridActor, 372460045);
	template<> FIRESIMULATION_API UClass* StaticClass<AGridActor>()
	{
		return AGridActor::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_AGridActor(Z_Construct_UClass_AGridActor, &AGridActor::StaticClass, TEXT("/Script/FireSimulation"), TEXT("AGridActor"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(AGridActor);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
