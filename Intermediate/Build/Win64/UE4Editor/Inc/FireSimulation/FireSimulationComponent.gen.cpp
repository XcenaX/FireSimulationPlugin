// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "FireSimulation/Public/FireSimulationComponent.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeFireSimulationComponent() {}
// Cross Module References
	FIRESIMULATION_API UClass* Z_Construct_UClass_UFireSimulationComponent_NoRegister();
	FIRESIMULATION_API UClass* Z_Construct_UClass_UFireSimulationComponent();
	ENGINE_API UClass* Z_Construct_UClass_USceneComponent();
	UPackage* Z_Construct_UPackage__Script_FireSimulation();
// End Cross Module References
	void UFireSimulationComponent::StaticRegisterNativesUFireSimulationComponent()
	{
	}
	UClass* Z_Construct_UClass_UFireSimulationComponent_NoRegister()
	{
		return UFireSimulationComponent::StaticClass();
	}
	struct Z_Construct_UClass_UFireSimulationComponent_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UFireSimulationComponent_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_USceneComponent,
		(UObject* (*)())Z_Construct_UPackage__Script_FireSimulation,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFireSimulationComponent_Statics::Class_MetaDataParams[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "ClassGroupNames", "Custom" },
		{ "HideCategories", "Trigger PhysicsVolume" },
		{ "IncludePath", "FireSimulationComponent.h" },
		{ "ModuleRelativePath", "Public/FireSimulationComponent.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UFireSimulationComponent_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UFireSimulationComponent>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UFireSimulationComponent_Statics::ClassParams = {
		&UFireSimulationComponent::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x00B000A4u,
		METADATA_PARAMS(Z_Construct_UClass_UFireSimulationComponent_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UFireSimulationComponent_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UFireSimulationComponent()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UFireSimulationComponent_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UFireSimulationComponent, 3452650987);
	template<> FIRESIMULATION_API UClass* StaticClass<UFireSimulationComponent>()
	{
		return UFireSimulationComponent::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UFireSimulationComponent(Z_Construct_UClass_UFireSimulationComponent, &UFireSimulationComponent::StaticClass, TEXT("/Script/FireSimulation"), TEXT("UFireSimulationComponent"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UFireSimulationComponent);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
