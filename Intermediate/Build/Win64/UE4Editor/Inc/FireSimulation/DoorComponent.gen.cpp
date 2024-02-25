// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "FireSimulation/Public/DoorComponent.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeDoorComponent() {}
// Cross Module References
	FIRESIMULATION_API UClass* Z_Construct_UClass_UDoorComponent_NoRegister();
	FIRESIMULATION_API UClass* Z_Construct_UClass_UDoorComponent();
	ENGINE_API UClass* Z_Construct_UClass_USceneComponent();
	UPackage* Z_Construct_UPackage__Script_FireSimulation();
	ENGINE_API UClass* Z_Construct_UClass_UBoxComponent_NoRegister();
	FIRESIMULATION_API UClass* Z_Construct_UClass_ARoomMarker_NoRegister();
// End Cross Module References
	void UDoorComponent::StaticRegisterNativesUDoorComponent()
	{
	}
	UClass* Z_Construct_UClass_UDoorComponent_NoRegister()
	{
		return UDoorComponent::StaticClass();
	}
	struct Z_Construct_UClass_UDoorComponent_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_DoorBounds_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_DoorBounds;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_ConnectedRoom1_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_ConnectedRoom1;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_ConnectedRoom2_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_ConnectedRoom2;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_bIsOpen_MetaData[];
#endif
		static void NewProp_bIsOpen_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_bIsOpen;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UDoorComponent_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_USceneComponent,
		(UObject* (*)())Z_Construct_UPackage__Script_FireSimulation,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UDoorComponent_Statics::Class_MetaDataParams[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "ClassGroupNames", "Custom" },
		{ "HideCategories", "Trigger PhysicsVolume" },
		{ "IncludePath", "DoorComponent.h" },
		{ "ModuleRelativePath", "Public/DoorComponent.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UDoorComponent_Statics::NewProp_DoorBounds_MetaData[] = {
		{ "Category", "Door" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DoorComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UDoorComponent_Statics::NewProp_DoorBounds = { "DoorBounds", nullptr, (EPropertyFlags)0x00100000000a0009, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UDoorComponent, DoorBounds), Z_Construct_UClass_UBoxComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_UDoorComponent_Statics::NewProp_DoorBounds_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UDoorComponent_Statics::NewProp_DoorBounds_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UDoorComponent_Statics::NewProp_ConnectedRoom1_MetaData[] = {
		{ "Category", "Door" },
		{ "ModuleRelativePath", "Public/DoorComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UDoorComponent_Statics::NewProp_ConnectedRoom1 = { "ConnectedRoom1", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UDoorComponent, ConnectedRoom1), Z_Construct_UClass_ARoomMarker_NoRegister, METADATA_PARAMS(Z_Construct_UClass_UDoorComponent_Statics::NewProp_ConnectedRoom1_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UDoorComponent_Statics::NewProp_ConnectedRoom1_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UDoorComponent_Statics::NewProp_ConnectedRoom2_MetaData[] = {
		{ "Category", "Door" },
		{ "ModuleRelativePath", "Public/DoorComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UDoorComponent_Statics::NewProp_ConnectedRoom2 = { "ConnectedRoom2", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UDoorComponent, ConnectedRoom2), Z_Construct_UClass_ARoomMarker_NoRegister, METADATA_PARAMS(Z_Construct_UClass_UDoorComponent_Statics::NewProp_ConnectedRoom2_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UDoorComponent_Statics::NewProp_ConnectedRoom2_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UDoorComponent_Statics::NewProp_bIsOpen_MetaData[] = {
		{ "Category", "Door" },
		{ "ModuleRelativePath", "Public/DoorComponent.h" },
	};
#endif
	void Z_Construct_UClass_UDoorComponent_Statics::NewProp_bIsOpen_SetBit(void* Obj)
	{
		((UDoorComponent*)Obj)->bIsOpen = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UDoorComponent_Statics::NewProp_bIsOpen = { "bIsOpen", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(UDoorComponent), &Z_Construct_UClass_UDoorComponent_Statics::NewProp_bIsOpen_SetBit, METADATA_PARAMS(Z_Construct_UClass_UDoorComponent_Statics::NewProp_bIsOpen_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UDoorComponent_Statics::NewProp_bIsOpen_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UDoorComponent_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UDoorComponent_Statics::NewProp_DoorBounds,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UDoorComponent_Statics::NewProp_ConnectedRoom1,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UDoorComponent_Statics::NewProp_ConnectedRoom2,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UDoorComponent_Statics::NewProp_bIsOpen,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UDoorComponent_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UDoorComponent>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UDoorComponent_Statics::ClassParams = {
		&UDoorComponent::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_UDoorComponent_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_UDoorComponent_Statics::PropPointers),
		0,
		0x00B000A4u,
		METADATA_PARAMS(Z_Construct_UClass_UDoorComponent_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UDoorComponent_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UDoorComponent()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UDoorComponent_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UDoorComponent, 2658723119);
	template<> FIRESIMULATION_API UClass* StaticClass<UDoorComponent>()
	{
		return UDoorComponent::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UDoorComponent(Z_Construct_UClass_UDoorComponent, &UDoorComponent::StaticClass, TEXT("/Script/FireSimulation"), TEXT("UDoorComponent"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UDoorComponent);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
