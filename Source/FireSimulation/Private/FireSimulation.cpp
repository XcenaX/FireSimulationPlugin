// Copyright Epic Games, Inc. All Rights Reserved.

#include "FireSimulation.h"
#include "FMaterialSelectionCustomization.h"

#define LOCTEXT_NAMESPACE "FFireSimulationModule"

void FFireSimulationModule::StartupModule()
{
	FPropertyEditorModule& PropertyEditorModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
    PropertyEditorModule.RegisterCustomClassLayout("FireSimulationActor", FOnGetDetailCustomizationInstance::CreateStatic(&FMaterialSelectionCustomization::MakeInstance));
}

void FFireSimulationModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FFireSimulationModule, FireSimulation)