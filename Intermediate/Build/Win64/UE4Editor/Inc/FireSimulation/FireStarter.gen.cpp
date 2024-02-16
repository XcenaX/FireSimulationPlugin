// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "FireSimulation/Public/FireStarter.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeFireStarter() {}
// Cross Module References
	FIRESIMULATION_API UClass* Z_Construct_UClass_AFireStarter_NoRegister();
	FIRESIMULATION_API UClass* Z_Construct_UClass_AFireStarter();
	ENGINE_API UClass* Z_Construct_UClass_AActor();
	UPackage* Z_Construct_UPackage__Script_FireSimulation();
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector();
	ENGINE_API UClass* Z_Construct_UClass_UTexture2D_NoRegister();
// End Cross Module References
	void AFireStarter::StaticRegisterNativesAFireStarter()
	{
	}
	UClass* Z_Construct_UClass_AFireStarter_NoRegister()
	{
		return AFireStarter::StaticClass();
	}
	struct Z_Construct_UClass_AFireStarter_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_StartPoint_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_StartPoint;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_SpreadTexture_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_SpreadTexture;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AFireStarter_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AActor,
		(UObject* (*)())Z_Construct_UPackage__Script_FireSimulation,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AFireStarter_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "FireStarter.h" },
		{ "ModuleRelativePath", "Public/FireStarter.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AFireStarter_Statics::NewProp_StartPoint_MetaData[] = {
		{ "Category", "Cellular Automaton" },
		{ "Comment", "// \xd0\x9d\xd0\xb0\xd1\x87\xd0\xb0\xd0\xbb\xd1\x8c\xd0\xbd\xd0\xb0\xd1\x8f \xd1\x82\xd0\xbe\xd1\x87\xd0\xba\xd0\xb0 \xd0\xb4\xd0\xbb\xd1\x8f \xd1\x80\xd0\xb0\xd1\x81\xd0\xbf\xd1\x80\xd0\xbe\xd1\x81\xd1\x82\xd1\x80\xd0\xb0\xd0\xbd\xd0\xb5\xd0\xbd\xd0\xb8\xd1\x8f \xd0\xba\xd0\xbb\xd0\xb5\xd1\x82\xd0\xbe\xd1\x87\xd0\xbd\xd1\x8b\xd1\x85 \xd0\xb0\xd0\xb2\xd1\x82\xd0\xbe\xd0\xbc\xd0\xb0\xd1\x82\xd0\xbe\xd0\xb2\n" },
		{ "ModuleRelativePath", "Public/FireStarter.h" },
		{ "ToolTip", "\xd0\x9d\xd0\xb0\xd1\x87\xd0\xb0\xd0\xbb\xd1\x8c\xd0\xbd\xd0\xb0\xd1\x8f \xd1\x82\xd0\xbe\xd1\x87\xd0\xba\xd0\xb0 \xd0\xb4\xd0\xbb\xd1\x8f \xd1\x80\xd0\xb0\xd1\x81\xd0\xbf\xd1\x80\xd0\xbe\xd1\x81\xd1\x82\xd1\x80\xd0\xb0\xd0\xbd\xd0\xb5\xd0\xbd\xd0\xb8\xd1\x8f \xd0\xba\xd0\xbb\xd0\xb5\xd1\x82\xd0\xbe\xd1\x87\xd0\xbd\xd1\x8b\xd1\x85 \xd0\xb0\xd0\xb2\xd1\x82\xd0\xbe\xd0\xbc\xd0\xb0\xd1\x82\xd0\xbe\xd0\xb2" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UClass_AFireStarter_Statics::NewProp_StartPoint = { "StartPoint", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AFireStarter, StartPoint), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(Z_Construct_UClass_AFireStarter_Statics::NewProp_StartPoint_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AFireStarter_Statics::NewProp_StartPoint_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AFireStarter_Statics::NewProp_SpreadTexture_MetaData[] = {
		{ "Category", "Cellular Automaton" },
		{ "Comment", "// \xd0\xa2\xd0\xb5\xd0\xba\xd1\x81\xd1\x82\xd1\x83\xd1\x80\xd0\xb0 \xd0\xb4\xd0\xbb\xd1\x8f \xd0\xb2\xd0\xb8\xd0\xb7\xd1\x83\xd0\xb0\xd0\xbb\xd0\xb8\xd0\xb7\xd0\xb0\xd1\x86\xd0\xb8\xd0\xb8 \xd0\xba\xd0\xbb\xd0\xb5\xd1\x82\xd0\xbe\xd1\x87\xd0\xbd\xd1\x8b\xd1\x85 \xd0\xb0\xd0\xb2\xd1\x82\xd0\xbe\xd0\xbc\xd0\xb0\xd1\x82\xd0\xbe\xd0\xb2\n" },
		{ "ModuleRelativePath", "Public/FireStarter.h" },
		{ "ToolTip", "\xd0\xa2\xd0\xb5\xd0\xba\xd1\x81\xd1\x82\xd1\x83\xd1\x80\xd0\xb0 \xd0\xb4\xd0\xbb\xd1\x8f \xd0\xb2\xd0\xb8\xd0\xb7\xd1\x83\xd0\xb0\xd0\xbb\xd0\xb8\xd0\xb7\xd0\xb0\xd1\x86\xd0\xb8\xd0\xb8 \xd0\xba\xd0\xbb\xd0\xb5\xd1\x82\xd0\xbe\xd1\x87\xd0\xbd\xd1\x8b\xd1\x85 \xd0\xb0\xd0\xb2\xd1\x82\xd0\xbe\xd0\xbc\xd0\xb0\xd1\x82\xd0\xbe\xd0\xb2" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AFireStarter_Statics::NewProp_SpreadTexture = { "SpreadTexture", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AFireStarter, SpreadTexture), Z_Construct_UClass_UTexture2D_NoRegister, METADATA_PARAMS(Z_Construct_UClass_AFireStarter_Statics::NewProp_SpreadTexture_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AFireStarter_Statics::NewProp_SpreadTexture_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AFireStarter_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AFireStarter_Statics::NewProp_StartPoint,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AFireStarter_Statics::NewProp_SpreadTexture,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_AFireStarter_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AFireStarter>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_AFireStarter_Statics::ClassParams = {
		&AFireStarter::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_AFireStarter_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_AFireStarter_Statics::PropPointers),
		0,
		0x009000A4u,
		METADATA_PARAMS(Z_Construct_UClass_AFireStarter_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_AFireStarter_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AFireStarter()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_AFireStarter_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(AFireStarter, 3764399961);
	template<> FIRESIMULATION_API UClass* StaticClass<AFireStarter>()
	{
		return AFireStarter::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_AFireStarter(Z_Construct_UClass_AFireStarter, &AFireStarter::StaticClass, TEXT("/Script/FireSimulation"), TEXT("AFireStarter"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(AFireStarter);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
