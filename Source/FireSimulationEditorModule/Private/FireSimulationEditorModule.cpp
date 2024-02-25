#include "FireSimulationEditorModule.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Input/SEditableTextBox.h"
#include "FireGridManager.h"
#include "UnrealEd.h"
#include "EngineUtils.h"
#include "GridActor.h"

static const FName FireSimulationTabName("FireSimulation");

#define LOCTEXT_NAMESPACE "FFireSimulationEditorModule"

void FFireSimulationEditorModule::StartupModule()
{
    FGlobalTabmanager::Get()->RegisterNomadTabSpawner(FireSimulationTabName, FOnSpawnTab::CreateRaw(this, &FFireSimulationEditorModule::OnSpawnPluginTab))
        .SetDisplayName(LOCTEXT("FFireSimulationTabTitle", "Fire Simulation"))
        .SetMenuType(ETabSpawnerMenuType::Enabled);
}

void FFireSimulationEditorModule::ShutdownModule()
{
    FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(FireSimulationTabName);
}

TSharedRef<SDockTab> FFireSimulationEditorModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
    CubesAmountTextBox = SNew(SEditableTextBox).HintText(LOCTEXT("CellSizeHint", "Enter amount of cubes in 1 dimension..."));
    
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
                CubesAmountTextBox.ToSharedRef()
            ]            
            +SVerticalBox::Slot()
            .FillHeight(1.f)
            .Padding(5)
            [
                SNew(SButton)
                .Text(LOCTEXT("InitializeButtonText", "Draw Grid"))
                .OnClicked(FOnClicked::CreateRaw(this, &FFireSimulationEditorModule::OnInitializeGridClicked))
                    
            ]
            + SVerticalBox::Slot()
            .FillHeight(1.f)
            .Padding(5)
            [
                SNew(SButton)
                    .Text(LOCTEXT("ClearButtonText", "Clear Grid"))
                    .OnClicked(FOnClicked::CreateRaw(this, &FFireSimulationEditorModule::OnClearGridClicked))

            ]
            +SVerticalBox::Slot()
            .FillHeight(1.f)
            .Padding(5)
            [
                SNew(SButton)
                    .Text(LOCTEXT("FillActorsButtonText", "Fill Grid with actors"))
                    .OnClicked(FOnClicked::CreateRaw(this, &FFireSimulationEditorModule::OnFillGridClicked))

            ]
        ];
}

FReply FFireSimulationEditorModule::OnInitializeGridClicked()
{
    if (CubesAmountTextBox.IsValid())
    {
        FString CubesAmountText = CubesAmountTextBox->GetText().ToString();
        int32 CubesAmount = FCString::Atoi(*CubesAmountText);     

        if (CubesAmount > 0)
        {
            // Поиск актора GridActor в мире
            if (GEditor)
            {
                UWorld* World = GEditor->GetEditorWorldContext().World();
                AGridActor* GridActor = nullptr;
                for (TActorIterator<AGridActor> It(World); It; ++It)
                {
                    GridActor = *It;
                    break;
                }

                UFireGridManager* GridManager = UFireGridManager::GetInstance();
                if (GridManager)
                {
                    GridManager->InitializeGrid(CubesAmount);
                    GridManager->DrawGrid(true, World, GridActor);
                }
            }
        }
    }
    return FReply::Handled();
}

FReply FFireSimulationEditorModule::OnClearGridClicked()
{
    if (GEditor)
    {
        UWorld* World = GEditor->GetEditorWorldContext().World();
        FlushPersistentDebugLines(World);
    }
    return FReply::Handled();
}

FReply FFireSimulationEditorModule::OnFillGridClicked()
{    
    UFireGridManager* GridManager = UFireGridManager::GetInstance();
    if (GridManager)
    {
        //#if WITH_EDITOR
        //#include "UnrealEd.h"
        if (GEditor)
        {
            UWorld* World = GEditor->GetEditorWorldContext().World();
            AGridActor* GridActor = nullptr;
            for (TActorIterator<AGridActor> It(World); It; ++It)
            {
                GridActor = *It;
                break;
            }
            GridManager->PopulateGridWithActors(World, GridActor);
        }
        //#endif
    }   
    return FReply::Handled();
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FFireSimulationEditorModule, FireSimulationEditor)
