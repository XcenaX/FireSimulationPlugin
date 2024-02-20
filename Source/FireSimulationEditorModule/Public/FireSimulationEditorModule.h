#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Input/SEditableTextBox.h"

class FFireSimulationEditorModule : public IModuleInterface
{
public:
    /** IModuleInterface implementation */
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;

private:
    /** Handle to the test tab */
    TSharedPtr<SDockTab> FireSimulationTab;

    /** Text box for inputting the cell size */
    TSharedPtr<SEditableTextBox> CellSizeTextBox;

    /** Callback for spawning the plugin tab */
    TSharedRef<SDockTab> OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs);

    /** Callback for when the 'Initialize Grid' button is clicked */
    FReply OnInitializeGridClicked();
};

DECLARE_LOG_CATEGORY_EXTERN(LogFireSimulationEditor, Log, All);

DEFINE_LOG_CATEGORY(LogFireSimulationEditor);