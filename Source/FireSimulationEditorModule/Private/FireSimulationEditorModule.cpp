#include "FireSimulationEditorModule.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Input/SEditableTextBox.h"
#include "FireGridManager.h"

static const FName FireSimulationTabName("FireSimulation");

#define LOCTEXT_NAMESPACE "FFireSimulationEditorModule"

void FFireSimulationEditorModule::StartupModule()
{
    FGlobalTabmanager::Get()->RegisterNomadTabSpawner(FireSimulationTabName, FOnSpawnTab::CreateRaw(this, &FFireSimulationEditorModule::OnSpawnPluginTab))
        .SetDisplayName(LOCTEXT("FFireSimulationTabTitle", "Fire Simulation"))
        .SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FFireSimulationEditorModule::ShutdownModule()
{
    FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(FireSimulationTabName);
}

TSharedRef<SDockTab> FFireSimulationEditorModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
    CellSizeTextBox = SNew(SEditableTextBox).HintText(LOCTEXT("CellSizeHint", "Enter Cell Size..."));

    return SNew(SDockTab)
        .TabRole(ETabRole::NomadTab)
        [
            SNew(SVerticalBox)
            +SVerticalBox::Slot()
            .FillHeight(1.f)
            .Padding(5)
            [
                SNew(STextBlock)
                .Text(LOCTEXT("FireGridManagerTab", "Fire Grid Manager"))
            ]
            +SVerticalBox::Slot()
            .FillHeight(1.f)
            .Padding(5)
            [
                CellSizeTextBox.ToSharedRef()
            ]
            +SVerticalBox::Slot()
            .FillHeight(1.f)
            .Padding(5)
            [
                SNew(SButton)
                .Text(LOCTEXT("InitializeButtonText", "Initialize Grid"))
                .OnClicked(this, &FFireSimulationEditorModule::OnInitializeGridClicked)
            ]
        ];
}

FReply FFireSimulationEditorModule::OnInitializeGridClicked()
{
    if (CellSizeTextBox.IsValid())
    {
        // Преобразование текста в число
        FString CellSizeText = CellSizeTextBox->GetText().ToString();
        float CellSize = FCString::Atof(*CellSizeText);
        
        if (CellSize > 0)
        {
            // Предполагаем, что у вас есть статический метод доступа или глобальный экземпляр UFireGridManager
            UFireGridManager* GridManager = UFireGridManager::GetInstance();
            if (GridManager)
            {
                GridManager->InitializeGrid(CellSize);
                // Возможно, вам также захочется вызвать здесь PopulateGridWithActors или другие методы
            }
        }
    }
    return FReply::Handled();
}


#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FFireSimulationEditorModule, FireSimulationEditor)
