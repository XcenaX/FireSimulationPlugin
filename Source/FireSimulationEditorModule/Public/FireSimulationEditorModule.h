#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "Widgets/Docking/SDockTab.h"

class FFireSimulationEditorModule : public IModuleInterface
{
public:
    /** IModuleInterface implementation */
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;

    void ShowNotification(FString message);

private:

    TSharedPtr<SDockTab> FireSimulationTab;

    TSharedPtr<SEditableTextBox> CubesAmountTextBox;
    TSharedPtr<SEditableTextBox> ThreadsTextBox;
    TSharedPtr<SEditableTextBox> FireSizeTextBox;
    
    TSharedPtr<SButton> PickFireButton;
    
    TSharedRef<SDockTab> OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs);

    FReply OnInitializeGridClicked();
    FReply OnClearGridClicked();
    FReply OnFillGridClicked();
    FReply OnPickActorClassClicked();
};