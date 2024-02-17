#include "FireSimulation.h"
#include "FMaterialSelectionCustomization.h"
#include <PropertyEditorModule.h>
#include "FireSimulationComponent.h"

#define LOCTEXT_NAMESPACE "FFireSimulationModule"

void FFireSimulationModule::StartupModule()
{
    FPropertyEditorModule& PropertyEditorModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
    PropertyEditorModule.RegisterCustomClassLayout(
        UFireSimulationComponent::StaticClass()->GetFName(),
        FOnGetDetailCustomizationInstance::CreateStatic(&FMaterialSelectionCustomization::MakeInstance)
    );

    // Уберите отмену регистрации отсюда
}

void FFireSimulationModule::ShutdownModule()
{
    if (FModuleManager::Get().IsModuleLoaded("PropertyEditor"))
    {
        FPropertyEditorModule& PropertyModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");
        PropertyModule.UnregisterCustomClassLayout("UFireSimulationComponent");
    }
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FFireSimulationModule, FireSimulation)