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
#include "GridOriginActor.h"

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
    GridLengthTextBox = SNew(SEditableTextBox).HintText(LOCTEXT("GridLengthHint", "Enter Grid Length..."));

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
            + SVerticalBox::Slot()
            .FillHeight(1.f)
            .Padding(5)
            [
                GridLengthTextBox.ToSharedRef()
            ]
            +SVerticalBox::Slot()
            .FillHeight(1.f)
            .Padding(5)
            [
                SNew(SButton)
                .Text(LOCTEXT("InitializeButtonText", "Initialize Grid"))
                .OnClicked(FOnClicked::CreateRaw(this, &FFireSimulationEditorModule::OnInitializeGridClicked))
                    
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
    FVector GridOrigin = FVector::ZeroVector; // Значение по умолчанию
    if (CubesAmountTextBox.IsValid() && GridLengthTextBox.IsValid())
    {
        FString CubesAmountText = CubesAmountTextBox->GetText().ToString();
        int32 CubesAmount = FCString::Atoi(*CubesAmountText); // Используйте Atoi для целых чисел

        FString GridLengthText = GridLengthTextBox->GetText().ToString();
        float GridLength = FCString::Atof(*GridLengthText);

        if (CubesAmount > 0 && GridLength > 0)
        {
            // Поиск актора GridOriginActor в мире
            if (GEditor)
            {
                UWorld* World = GEditor->GetEditorWorldContext().World();
                for (TActorIterator<AGridOriginActor> It(World); It; ++It)
                {
                    AGridOriginActor* GridOriginActor = *It;
                    if (GridOriginActor)
                    {
                        GridOrigin = GridOriginActor->GetActorLocation();
                        break; // Предполагаем, что в мире только один такой актор
                    }
                }

                UFireGridManager* GridManager = UFireGridManager::GetInstance();
                if (GridManager)
                {
                    GridManager->InitializeGrid(CubesAmount, GridLength, GridOrigin);
                    GridManager->DrawGrid(true);
                }
            }
        }
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
            GridManager->PopulateGridWithActors(World);
        }
        //#endif
    }   
    return FReply::Handled();
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FFireSimulationEditorModule, FireSimulationEditor)
