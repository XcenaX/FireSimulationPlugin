// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class UWorld;
class AActor;
#ifdef FIRESIMULATION_FireGridManager_generated_h
#error "FireGridManager.generated.h already included, missing '#pragma once' in FireGridManager.h"
#endif
#define FIRESIMULATION_FireGridManager_generated_h

#define TestProject_Plugins_FireSimulation_Source_FireSimulation_Public_FireGridManager_h_10_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FGridCell_Statics; \
	FIRESIMULATION_API static class UScriptStruct* StaticStruct();


template<> FIRESIMULATION_API UScriptStruct* StaticStruct<struct FGridCell>();

#define TestProject_Plugins_FireSimulation_Source_FireSimulation_Public_FireGridManager_h_24_SPARSE_DATA
#define TestProject_Plugins_FireSimulation_Source_FireSimulation_Public_FireGridManager_h_24_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execPopulateGridWithActors); \
	DECLARE_FUNCTION(execDrawGrid); \
	DECLARE_FUNCTION(execInitializeGrid);


#define TestProject_Plugins_FireSimulation_Source_FireSimulation_Public_FireGridManager_h_24_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execPopulateGridWithActors); \
	DECLARE_FUNCTION(execDrawGrid); \
	DECLARE_FUNCTION(execInitializeGrid);


#define TestProject_Plugins_FireSimulation_Source_FireSimulation_Public_FireGridManager_h_24_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUFireGridManager(); \
	friend struct Z_Construct_UClass_UFireGridManager_Statics; \
public: \
	DECLARE_CLASS(UFireGridManager, UObject, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/FireSimulation"), NO_API) \
	DECLARE_SERIALIZER(UFireGridManager)


#define TestProject_Plugins_FireSimulation_Source_FireSimulation_Public_FireGridManager_h_24_INCLASS \
private: \
	static void StaticRegisterNativesUFireGridManager(); \
	friend struct Z_Construct_UClass_UFireGridManager_Statics; \
public: \
	DECLARE_CLASS(UFireGridManager, UObject, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/FireSimulation"), NO_API) \
	DECLARE_SERIALIZER(UFireGridManager)


#define TestProject_Plugins_FireSimulation_Source_FireSimulation_Public_FireGridManager_h_24_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UFireGridManager(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UFireGridManager) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UFireGridManager); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UFireGridManager); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UFireGridManager(UFireGridManager&&); \
	NO_API UFireGridManager(const UFireGridManager&); \
public:


#define TestProject_Plugins_FireSimulation_Source_FireSimulation_Public_FireGridManager_h_24_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UFireGridManager(UFireGridManager&&); \
	NO_API UFireGridManager(const UFireGridManager&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UFireGridManager); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UFireGridManager); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UFireGridManager)


#define TestProject_Plugins_FireSimulation_Source_FireSimulation_Public_FireGridManager_h_24_PRIVATE_PROPERTY_OFFSET
#define TestProject_Plugins_FireSimulation_Source_FireSimulation_Public_FireGridManager_h_21_PROLOG
#define TestProject_Plugins_FireSimulation_Source_FireSimulation_Public_FireGridManager_h_24_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	TestProject_Plugins_FireSimulation_Source_FireSimulation_Public_FireGridManager_h_24_PRIVATE_PROPERTY_OFFSET \
	TestProject_Plugins_FireSimulation_Source_FireSimulation_Public_FireGridManager_h_24_SPARSE_DATA \
	TestProject_Plugins_FireSimulation_Source_FireSimulation_Public_FireGridManager_h_24_RPC_WRAPPERS \
	TestProject_Plugins_FireSimulation_Source_FireSimulation_Public_FireGridManager_h_24_INCLASS \
	TestProject_Plugins_FireSimulation_Source_FireSimulation_Public_FireGridManager_h_24_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define TestProject_Plugins_FireSimulation_Source_FireSimulation_Public_FireGridManager_h_24_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	TestProject_Plugins_FireSimulation_Source_FireSimulation_Public_FireGridManager_h_24_PRIVATE_PROPERTY_OFFSET \
	TestProject_Plugins_FireSimulation_Source_FireSimulation_Public_FireGridManager_h_24_SPARSE_DATA \
	TestProject_Plugins_FireSimulation_Source_FireSimulation_Public_FireGridManager_h_24_RPC_WRAPPERS_NO_PURE_DECLS \
	TestProject_Plugins_FireSimulation_Source_FireSimulation_Public_FireGridManager_h_24_INCLASS_NO_PURE_DECLS \
	TestProject_Plugins_FireSimulation_Source_FireSimulation_Public_FireGridManager_h_24_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> FIRESIMULATION_API UClass* StaticClass<class UFireGridManager>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID TestProject_Plugins_FireSimulation_Source_FireSimulation_Public_FireGridManager_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
