#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "GridActor.h"
#include "Widgets/Docking/SDockTab.h"

class FFireSimulationEditorModule : public IModuleInterface
{
public:
    /** IModuleInterface implementation */
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;

    void ShowNotification(FString message);

    void DrawGrid(bool bVisible, UWorld* World, AGridActor* GridActor, int32 CellSize);

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