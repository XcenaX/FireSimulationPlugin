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
    
    TSharedRef<SDockTab> OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs);

    /** Callback for when the 'Initialize Grid' button is clicked */
    FReply OnInitializeGridClicked();
    FReply OnClearGridClicked();
    FReply OnFillGridClicked();
    void OnParticleSystemSelected(const FAssetData& AssetData);
    FReply OnPickActorClassClicked();
};