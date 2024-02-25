// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
struct FDoorEdge;
struct FRoomNode;
#ifdef FIRESIMULATION_BuildingGraph_generated_h
#error "BuildingGraph.generated.h already included, missing '#pragma once' in BuildingGraph.h"
#endif
#define FIRESIMULATION_BuildingGraph_generated_h

#define TestProject_Plugins_FireSimulation_Source_FireSimulation_Public_BuildingGraph_h_36_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FDoorEdge_Statics; \
	FIRESIMULATION_API static class UScriptStruct* StaticStruct();


template<> FIRESIMULATION_API UScriptStruct* StaticStruct<struct FDoorEdge>();

#define TestProject_Plugins_FireSimulation_Source_FireSimulation_Public_BuildingGraph_h_18_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FRoomNode_Statics; \
	FIRESIMULATION_API static class UScriptStruct* StaticStruct();


template<> FIRESIMULATION_API UScriptStruct* StaticStruct<struct FRoomNode>();

#define TestProject_Plugins_FireSimulation_Source_FireSimulation_Public_BuildingGraph_h_69_SPARSE_DATA
#define TestProject_Plugins_FireSimulation_Source_FireSimulation_Public_BuildingGraph_h_69_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execCalculateRoomAreas); \
	DECLARE_FUNCTION(execAddDoor); \
	DECLARE_FUNCTION(execAddRoom); \
	DECLARE_FUNCTION(execInitializeGraph);


#define TestProject_Plugins_FireSimulation_Source_FireSimulation_Public_BuildingGraph_h_69_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execCalculateRoomAreas); \
	DECLARE_FUNCTION(execAddDoor); \
	DECLARE_FUNCTION(execAddRoom); \
	DECLARE_FUNCTION(execInitializeGraph);


#define TestProject_Plugins_FireSimulation_Source_FireSimulation_Public_BuildingGraph_h_69_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUBuildingGraph(); \
	friend struct Z_Construct_UClass_UBuildingGraph_Statics; \
public: \
	DECLARE_CLASS(UBuildingGraph, UObject, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/FireSimulation"), NO_API) \
	DECLARE_SERIALIZER(UBuildingGraph)


#define TestProject_Plugins_FireSimulation_Source_FireSimulation_Public_BuildingGraph_h_69_INCLASS \
private: \
	static void StaticRegisterNativesUBuildingGraph(); \
	friend struct Z_Construct_UClass_UBuildingGraph_Statics; \
public: \
	DECLARE_CLASS(UBuildingGraph, UObject, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/FireSimulation"), NO_API) \
	DECLARE_SERIALIZER(UBuildingGraph)


#define TestProject_Plugins_FireSimulation_Source_FireSimulation_Public_BuildingGraph_h_69_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UBuildingGraph(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UBuildingGraph) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UBuildingGraph); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UBuildingGraph); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UBuildingGraph(UBuildingGraph&&); \
	NO_API UBuildingGraph(const UBuildingGraph&); \
public:


#define TestProject_Plugins_FireSimulation_Source_FireSimulation_Public_BuildingGraph_h_69_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UBuildingGraph(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer) { }; \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UBuildingGraph(UBuildingGraph&&); \
	NO_API UBuildingGraph(const UBuildingGraph&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UBuildingGraph); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UBuildingGraph); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UBuildingGraph)


#define TestProject_Plugins_FireSimulation_Source_FireSimulation_Public_BuildingGraph_h_69_PRIVATE_PROPERTY_OFFSET \
	FORCEINLINE static uint32 __PPO__Rooms() { return STRUCT_OFFSET(UBuildingGraph, Rooms); } \
	FORCEINLINE static uint32 __PPO__Doors() { return STRUCT_OFFSET(UBuildingGraph, Doors); }


#define TestProject_Plugins_FireSimulation_Source_FireSimulation_Public_BuildingGraph_h_66_PROLOG
#define TestProject_Plugins_FireSimulation_Source_FireSimulation_Public_BuildingGraph_h_69_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	TestProject_Plugins_FireSimulation_Source_FireSimulation_Public_BuildingGraph_h_69_PRIVATE_PROPERTY_OFFSET \
	TestProject_Plugins_FireSimulation_Source_FireSimulation_Public_BuildingGraph_h_69_SPARSE_DATA \
	TestProject_Plugins_FireSimulation_Source_FireSimulation_Public_BuildingGraph_h_69_RPC_WRAPPERS \
	TestProject_Plugins_FireSimulation_Source_FireSimulation_Public_BuildingGraph_h_69_INCLASS \
	TestProject_Plugins_FireSimulation_Source_FireSimulation_Public_BuildingGraph_h_69_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define TestProject_Plugins_FireSimulation_Source_FireSimulation_Public_BuildingGraph_h_69_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	TestProject_Plugins_FireSimulation_Source_FireSimulation_Public_BuildingGraph_h_69_PRIVATE_PROPERTY_OFFSET \
	TestProject_Plugins_FireSimulation_Source_FireSimulation_Public_BuildingGraph_h_69_SPARSE_DATA \
	TestProject_Plugins_FireSimulation_Source_FireSimulation_Public_BuildingGraph_h_69_RPC_WRAPPERS_NO_PURE_DECLS \
	TestProject_Plugins_FireSimulation_Source_FireSimulation_Public_BuildingGraph_h_69_INCLASS_NO_PURE_DECLS \
	TestProject_Plugins_FireSimulation_Source_FireSimulation_Public_BuildingGraph_h_69_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> FIRESIMULATION_API UClass* StaticClass<class UBuildingGraph>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID TestProject_Plugins_FireSimulation_Source_FireSimulation_Public_BuildingGraph_h


#define FOREACH_ENUM_EDOORSTATUS(op) \
	op(EDoorStatus::Closed) \
	op(EDoorStatus::Open) \
	op(EDoorStatus::NoDoor) 

enum class EDoorStatus : uint8;
template<> FIRESIMULATION_API UEnum* StaticEnum<EDoorStatus>();

PRAGMA_ENABLE_DEPRECATION_WARNINGS
