#include "FireSimulation.h"
#include "FMaterialSelectionCustomization.h"
#include <PropertyEditorModule.h>

#define LOCTEXT_NAMESPACE "FFireSimulationModule"

void FFireSimulationModule::StartupModule()
{
    FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
    PropertyModule.RegisterCustomClassLayout(
        "UFireSimulationComponent", // Имя класса компонента, который вы хотите кастомизировать
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