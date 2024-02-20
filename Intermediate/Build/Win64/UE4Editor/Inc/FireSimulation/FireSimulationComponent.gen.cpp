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
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_SelectedMaterial_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_SelectedMaterial;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_IsBurning_MetaData[];
#endif
		static void NewProp_IsBurning_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_IsBurning;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
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
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFireSimulationComponent_Statics::NewProp_SelectedMaterial_MetaData[] = {
		{ "Comment", "// \xd0\x9c\xd0\xb0\xd1\x82\xd0\xb5\xd1\x80\xd0\xb8\xd0\xb0\xd0\xbb \xd0\xbe\xd0\xb1\xd1\x8a\xd0\xb5\xd0\xba\xd1\x82\xd0\xb0, \xd0\xbd\xd1\x83\xd0\xb6\xd0\xb5\xd0\xbd \xd0\xb4\xd0\xbb\xd1\x8f \xd1\x80\xd0\xb0\xd1\x81\xd1\x87\xd0\xb5\xd1\x82\xd0\xbe\xd0\xb2 \xd1\x80\xd0\xb0\xd1\x81\xd0\xbf\xd1\x80\xd0\xbe\xd1\x81\xd1\x82\xd1\x80\xd0\xb0\xd0\xbd\xd0\xb5\xd0\xbd\xd0\xb8\xd1\x8f \xd0\xbe\xd0\xb3\xd0\xbd\xd1\x8f \xd0\xb8 \xd0\xb4\xd1\x8b\xd0\xbc\xd0\xb0\n" },
		{ "Hidden", "" },
		{ "ModuleRelativePath", "Public/FireSimulationComponent.h" },
		{ "ToolTip", "\xd0\x9c\xd0\xb0\xd1\x82\xd0\xb5\xd1\x80\xd0\xb8\xd0\xb0\xd0\xbb \xd0\xbe\xd0\xb1\xd1\x8a\xd0\xb5\xd0\xba\xd1\x82\xd0\xb0, \xd0\xbd\xd1\x83\xd0\xb6\xd0\xb5\xd0\xbd \xd0\xb4\xd0\xbb\xd1\x8f \xd1\x80\xd0\xb0\xd1\x81\xd1\x87\xd0\xb5\xd1\x82\xd0\xbe\xd0\xb2 \xd1\x80\xd0\xb0\xd1\x81\xd0\xbf\xd1\x80\xd0\xbe\xd1\x81\xd1\x82\xd1\x80\xd0\xb0\xd0\xbd\xd0\xb5\xd0\xbd\xd0\xb8\xd1\x8f \xd0\xbe\xd0\xb3\xd0\xbd\xd1\x8f \xd0\xb8 \xd0\xb4\xd1\x8b\xd0\xbc\xd0\xb0" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UClass_UFireSimulationComponent_Statics::NewProp_SelectedMaterial = { "SelectedMaterial", nullptr, (EPropertyFlags)0x0010000000004000, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UFireSimulationComponent, SelectedMaterial), METADATA_PARAMS(Z_Construct_UClass_UFireSimulationComponent_Statics::NewProp_SelectedMaterial_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UFireSimulationComponent_Statics::NewProp_SelectedMaterial_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFireSimulationComponent_Statics::NewProp_IsBurning_MetaData[] = {
		{ "Category", "Fire Simulation" },
		{ "Comment", "// \xd0\xa1\xd0\xb2\xd0\xbe\xd0\xb9\xd1\x81\xd1\x82\xd0\xb2\xd0\xbe \xd0\xbe\xd0\xb7\xd0\xbd\xd0\xb0\xd1\x87\xd0\xb0\xd0\xb5\xd1\x82 \xd1\x8f\xd0\xb2\xd0\xbb\xd1\x8f\xd0\xb5\xd1\x82\xd1\x81\xd1\x8f \xd0\xbb\xd0\xb8 \xd1\x8d\xd1\x82\xd0\xbe\xd1\x82 \xd0\xbe\xd0\xb1\xd1\x8c\xd0\xb5\xd0\xba\xd1\x82 \xd1\x82\xd0\xbe\xd1\x87\xd0\xba\xd0\xbe\xd0\xb9 \xd0\xb2\xd0\xbe\xd0\xb7\xd0\xb3\xd0\xbe\xd1\x80\xd0\xb0\xd0\xbd\xd0\xb8\xd1\x8f\n" },
		{ "ModuleRelativePath", "Public/FireSimulationComponent.h" },
		{ "ToolTip", "\xd0\xa1\xd0\xb2\xd0\xbe\xd0\xb9\xd1\x81\xd1\x82\xd0\xb2\xd0\xbe \xd0\xbe\xd0\xb7\xd0\xbd\xd0\xb0\xd1\x87\xd0\xb0\xd0\xb5\xd1\x82 \xd1\x8f\xd0\xb2\xd0\xbb\xd1\x8f\xd0\xb5\xd1\x82\xd1\x81\xd1\x8f \xd0\xbb\xd0\xb8 \xd1\x8d\xd1\x82\xd0\xbe\xd1\x82 \xd0\xbe\xd0\xb1\xd1\x8c\xd0\xb5\xd0\xba\xd1\x82 \xd1\x82\xd0\xbe\xd1\x87\xd0\xba\xd0\xbe\xd0\xb9 \xd0\xb2\xd0\xbe\xd0\xb7\xd0\xb3\xd0\xbe\xd1\x80\xd0\xb0\xd0\xbd\xd0\xb8\xd1\x8f" },
	};
#endif
	void Z_Construct_UClass_UFireSimulationComponent_Statics::NewProp_IsBurning_SetBit(void* Obj)
	{
		((UFireSimulationComponent*)Obj)->IsBurning = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UFireSimulationComponent_Statics::NewProp_IsBurning = { "IsBurning", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(UFireSimulationComponent), &Z_Construct_UClass_UFireSimulationComponent_Statics::NewProp_IsBurning_SetBit, METADATA_PARAMS(Z_Construct_UClass_UFireSimulationComponent_Statics::NewProp_IsBurning_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UFireSimulationComponent_Statics::NewProp_IsBurning_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UFireSimulationComponent_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFireSimulationComponent_Statics::NewProp_SelectedMaterial,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFireSimulationComponent_Statics::NewProp_IsBurning,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UFireSimulationComponent_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UFireSimulationComponent>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UFireSimulationComponent_Statics::ClassParams = {
		&UFireSimulationComponent::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_UFireSimulationComponent_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_UFireSimulationComponent_Statics::PropPointers),
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
	IMPLEMENT_CLASS(UFireSimulationComponent, 18979166);
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
