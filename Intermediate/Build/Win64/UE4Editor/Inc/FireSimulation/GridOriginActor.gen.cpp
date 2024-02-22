// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "FireSimulation/Public/GridOriginActor.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeGridOriginActor() {}
// Cross Module References
	FIRESIMULATION_API UClass* Z_Construct_UClass_AGridOriginActor_NoRegister();
	FIRESIMULATION_API UClass* Z_Construct_UClass_AGridOriginActor();
	ENGINE_API UClass* Z_Construct_UClass_AActor();
	UPackage* Z_Construct_UPackage__Script_FireSimulation();
	ENGINE_API UClass* Z_Construct_UClass_USphereComponent_NoRegister();
// End Cross Module References
	void AGridOriginActor::StaticRegisterNativesAGridOriginActor()
	{
	}
	UClass* Z_Construct_UClass_AGridOriginActor_NoRegister()
	{
		return AGridOriginActor::StaticClass();
	}
	struct Z_Construct_UClass_AGridOriginActor_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_SphereComponent_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_SphereComponent;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AGridOriginActor_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AActor,
		(UObject* (*)())Z_Construct_UPackage__Script_FireSimulation,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AGridOriginActor_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "GridOriginActor.h" },
		{ "ModuleRelativePath", "Public/GridOriginActor.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AGridOriginActor_Statics::NewProp_SphereComponent_MetaData[] = {
		{ "Category", "GridOriginActor" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/GridOriginActor.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AGridOriginActor_Statics::NewProp_SphereComponent = { "SphereComponent", nullptr, (EPropertyFlags)0x00200800000a0009, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AGridOriginActor, SphereComponent), Z_Construct_UClass_USphereComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_AGridOriginActor_Statics::NewProp_SphereComponent_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AGridOriginActor_Statics::NewProp_SphereComponent_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AGridOriginActor_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AGridOriginActor_Statics::NewProp_SphereComponent,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_AGridOriginActor_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AGridOriginActor>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_AGridOriginActor_Statics::ClassParams = {
		&AGridOriginActor::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_AGridOriginActor_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_AGridOriginActor_Statics::PropPointers),
		0,
		0x009000A4u,
		METADATA_PARAMS(Z_Construct_UClass_AGridOriginActor_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_AGridOriginActor_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AGridOriginActor()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_AGridOriginActor_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(AGridOriginActor, 3870007045);
	template<> FIRESIMULATION_API UClass* StaticClass<AGridOriginActor>()
	{
		return AGridOriginActor::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_AGridOriginActor(Z_Construct_UClass_AGridOriginActor, &AGridOriginActor::StaticClass, TEXT("/Script/FireSimulation"), TEXT("AGridOriginActor"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(AGridOriginActor);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
