// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "FireSimulation/Public/RoomMarker.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeRoomMarker() {}
// Cross Module References
	FIRESIMULATION_API UClass* Z_Construct_UClass_ARoomMarker_NoRegister();
	FIRESIMULATION_API UClass* Z_Construct_UClass_ARoomMarker();
	ENGINE_API UClass* Z_Construct_UClass_AActor();
	UPackage* Z_Construct_UPackage__Script_FireSimulation();
	ENGINE_API UClass* Z_Construct_UClass_UBoxComponent_NoRegister();
// End Cross Module References
	void ARoomMarker::StaticRegisterNativesARoomMarker()
	{
	}
	UClass* Z_Construct_UClass_ARoomMarker_NoRegister()
	{
		return ARoomMarker::StaticClass();
	}
	struct Z_Construct_UClass_ARoomMarker_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_RoomBounds_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_RoomBounds;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_RoomID_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_RoomID;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ARoomMarker_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AActor,
		(UObject* (*)())Z_Construct_UPackage__Script_FireSimulation,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ARoomMarker_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "RoomMarker.h" },
		{ "ModuleRelativePath", "Public/RoomMarker.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ARoomMarker_Statics::NewProp_RoomBounds_MetaData[] = {
		{ "Category", "Room" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/RoomMarker.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ARoomMarker_Statics::NewProp_RoomBounds = { "RoomBounds", nullptr, (EPropertyFlags)0x00100000000a0009, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ARoomMarker, RoomBounds), Z_Construct_UClass_UBoxComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_ARoomMarker_Statics::NewProp_RoomBounds_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ARoomMarker_Statics::NewProp_RoomBounds_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ARoomMarker_Statics::NewProp_RoomID_MetaData[] = {
		{ "Category", "Room" },
		{ "Comment", "// Custom properties\n" },
		{ "ModuleRelativePath", "Public/RoomMarker.h" },
		{ "ToolTip", "Custom properties" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UClass_ARoomMarker_Statics::NewProp_RoomID = { "RoomID", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ARoomMarker, RoomID), METADATA_PARAMS(Z_Construct_UClass_ARoomMarker_Statics::NewProp_RoomID_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ARoomMarker_Statics::NewProp_RoomID_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ARoomMarker_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ARoomMarker_Statics::NewProp_RoomBounds,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ARoomMarker_Statics::NewProp_RoomID,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_ARoomMarker_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ARoomMarker>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_ARoomMarker_Statics::ClassParams = {
		&ARoomMarker::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_ARoomMarker_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_ARoomMarker_Statics::PropPointers),
		0,
		0x009000A4u,
		METADATA_PARAMS(Z_Construct_UClass_ARoomMarker_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_ARoomMarker_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ARoomMarker()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_ARoomMarker_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(ARoomMarker, 3672693329);
	template<> FIRESIMULATION_API UClass* StaticClass<ARoomMarker>()
	{
		return ARoomMarker::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_ARoomMarker(Z_Construct_UClass_ARoomMarker, &ARoomMarker::StaticClass, TEXT("/Script/FireSimulation"), TEXT("ARoomMarker"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(ARoomMarker);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
