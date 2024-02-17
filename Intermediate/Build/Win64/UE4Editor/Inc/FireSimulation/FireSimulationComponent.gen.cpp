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
	FIRESIMULATION_API UScriptStruct* Z_Construct_UScriptStruct_FMaterialData();
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
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_MaterialOptions_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_MaterialOptions_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_MaterialOptions;
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
		{ "Category", "Fire Simulation" },
		{ "Comment", "/*UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = \"Fire Simulation\")\n    TArray<UMaterialInterface*> AvailableMaterials;*/" },
		{ "ModuleRelativePath", "Public/FireSimulationComponent.h" },
		{ "ToolTip", "UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = \"Fire Simulation\")\n    TArray<UMaterialInterface*> AvailableMaterials;" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UClass_UFireSimulationComponent_Statics::NewProp_SelectedMaterial = { "SelectedMaterial", nullptr, (EPropertyFlags)0x0010000000020015, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UFireSimulationComponent, SelectedMaterial), METADATA_PARAMS(Z_Construct_UClass_UFireSimulationComponent_Statics::NewProp_SelectedMaterial_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UFireSimulationComponent_Statics::NewProp_SelectedMaterial_MetaData)) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UClass_UFireSimulationComponent_Statics::NewProp_MaterialOptions_Inner = { "MaterialOptions", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FMaterialData, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFireSimulationComponent_Statics::NewProp_MaterialOptions_MetaData[] = {
		{ "Category", "Fire Simulation" },
		{ "Comment", "// \xd0\x9c\xd0\xb0\xd1\x81\xd1\x81\xd0\xb8\xd0\xb2 \xd0\xb4\xd0\xbb\xd1\x8f \xd1\x85\xd1\x80\xd0\xb0\xd0\xbd\xd0\xb5\xd0\xbd\xd0\xb8\xd1\x8f \xd0\xb7\xd0\xb0\xd0\xb3\xd1\x80\xd1\x83\xd0\xb6\xd0\xb5\xd0\xbd\xd0\xbd\xd1\x8b\xd1\x85 \xd0\xb4\xd0\xb0\xd0\xbd\xd0\xbd\xd1\x8b\xd1\x85 \xd0\xbe \xd0\xbc\xd0\xb0\xd1\x82\xd0\xb5\xd1\x80\xd0\xb8\xd0\xb0\xd0\xbb\xd0\xb0\xd1\x85\n" },
		{ "ModuleRelativePath", "Public/FireSimulationComponent.h" },
		{ "ToolTip", "\xd0\x9c\xd0\xb0\xd1\x81\xd1\x81\xd0\xb8\xd0\xb2 \xd0\xb4\xd0\xbb\xd1\x8f \xd1\x85\xd1\x80\xd0\xb0\xd0\xbd\xd0\xb5\xd0\xbd\xd0\xb8\xd1\x8f \xd0\xb7\xd0\xb0\xd0\xb3\xd1\x80\xd1\x83\xd0\xb6\xd0\xb5\xd0\xbd\xd0\xbd\xd1\x8b\xd1\x85 \xd0\xb4\xd0\xb0\xd0\xbd\xd0\xbd\xd1\x8b\xd1\x85 \xd0\xbe \xd0\xbc\xd0\xb0\xd1\x82\xd0\xb5\xd1\x80\xd0\xb8\xd0\xb0\xd0\xbb\xd0\xb0\xd1\x85" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UClass_UFireSimulationComponent_Statics::NewProp_MaterialOptions = { "MaterialOptions", nullptr, (EPropertyFlags)0x0010000000000015, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UFireSimulationComponent, MaterialOptions), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UClass_UFireSimulationComponent_Statics::NewProp_MaterialOptions_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UFireSimulationComponent_Statics::NewProp_MaterialOptions_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UFireSimulationComponent_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFireSimulationComponent_Statics::NewProp_SelectedMaterial,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFireSimulationComponent_Statics::NewProp_MaterialOptions_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFireSimulationComponent_Statics::NewProp_MaterialOptions,
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
	IMPLEMENT_CLASS(UFireSimulationComponent, 1632694660);
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
