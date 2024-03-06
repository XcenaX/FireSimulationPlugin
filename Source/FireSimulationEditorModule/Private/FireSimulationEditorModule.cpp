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
#include "Kismet2/SClassPickerDialog.h"
#include "ClassViewerModule.h"
#include "ClassViewerFilter.h"
#include <IContentBrowserSingleton.h>
#include <ContentBrowserModule.h>
#include "Widgets/Input/SEditableTextBox.h"
#include "Widgets/Notifications/SNotificationList.h"
#include "Framework/Notifications/NotificationManager.h"

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
    ThreadsTextBox = SNew(SEditableTextBox).HintText(LOCTEXT("ThreadsHint", "Enter amount of threads to use in fire simulation..."));

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
                ThreadsTextBox.ToSharedRef()
            ]
            +SVerticalBox::Slot()
            .FillHeight(1.f)
            .Padding(5)
            [
                SNew(SButton)
                    .Text(LOCTEXT("PickActorClassButtonText", "Pick Fire Visualisation"))
                    .OnClicked(FOnClicked::CreateRaw(this, &FFireSimulationEditorModule::OnPickActorClassClicked))
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

        FString ThreadsText = ThreadsTextBox->GetText().ToString();
        int32 Threads = FCString::Atoi(*ThreadsText);

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
                    if (CubesAmount > 30) {
                        ShowNotification("Building a grid with so many cells can take up a lot of resources! Operation cancelled!");
                    }
                    else {
                        GridManager->InitializeGrid(CubesAmount, Threads);
                        GridManager->DrawGrid(true, World, GridActor);
                    }
                }
            }
        }
        else {
            ShowNotification("Enter cubes amount per dimension to draw Grid!");
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
    FString CubesAmountText = CubesAmountTextBox->GetText().ToString();
    int32 CubesAmount = FCString::Atoi(*CubesAmountText);

    FString ThreadsText = ThreadsTextBox->GetText().ToString();
    int32 Threads = FCString::Atoi(*ThreadsText);

    UFireGridManager* GridManager = UFireGridManager::GetInstance();
    if (GridManager && CubesAmount > 0)
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
            GridManager->InitializeGrid(CubesAmount, Threads);
            GridManager->PopulateGridWithActors(World, GridActor);
            ShowNotification("Grid was successfully filled with Actors!");

        }
        //#endif
    }   
    return FReply::Handled();
}

FReply FFireSimulationEditorModule::OnPickActorClassClicked()
{
    /*FClassViewerInitializationOptions Options;
    Options.Mode = EClassViewerMode::ClassPicker;
    Options.DisplayMode = EClassViewerDisplayMode::ListView;    
    
    const FText TitleText = FText::FromString(TEXT("Выберите класс актора"));
    UClass* ChosenClass = nullptr;
    const bool bPressedOk = SClassPickerDialog::PickClass(TitleText, Options, ChosenClass, AActor::StaticClass());

    if (bPressedOk && ChosenClass != nullptr)
    {
        SelectedActorClass = ChosenClass;
        UFireGridManager::GetInstance()->FireActor = SelectedActorClass;
    }*/


    // Настройка конфигурации пикера ассетов
    FAssetPickerConfig AssetPickerConfig;
    AssetPickerConfig.Filter.ClassNames.Add(UParticleSystem::StaticClass()->GetFName());
    AssetPickerConfig.OnAssetSelected = FOnAssetSelected::CreateLambda([this](const FAssetData& AssetData)
        {
            UObject* SelectedObject = AssetData.GetAsset();
            UFireGridManager::GetInstance()->SelectedParticle = SelectedObject;

            ShowNotification("Fire Visualisation was picked!");
        });

    // Создание виджета для пикера ассетов
    FContentBrowserModule& ContentBrowserModule = FModuleManager::LoadModuleChecked<FContentBrowserModule>("ContentBrowser");
    TSharedRef<SWidget> AssetPicker = SNew(SBox)
        .WidthOverride(500.f)
        .HeightOverride(400.f)
        [
            ContentBrowserModule.Get().CreateAssetPicker(AssetPickerConfig)
        ];

    // Создание и отображение диалогового окна
    TSharedRef<SWindow> PickerWindow = SNew(SWindow)
        .Title(FText::FromString("Pick Fire visualisation"))
        .ClientSize(FVector2D(600, 500))
        [
            AssetPicker
        ];

    FSlateApplication::Get().AddModalWindow(PickerWindow, nullptr, false);


    return FReply::Handled();
}

//void FFireSimulationEditorModule::OnParticleSystemSelected(const FAssetData& AssetData) {
//    UParticleSystem* SelectedParticleSystem = Cast<UParticleSystem>(AssetData.GetAsset());
//    if (SelectedParticleSystem)
//    {
//        SelectedActorClass = SelectedParticleSystem;
//    }
//}
void FFireSimulationEditorModule::ShowNotification(FString message) {
    FNotificationInfo Info(FText::FromString(message));
    Info.ExpireDuration = 5.0f;
    FSlateNotificationManager::Get().AddNotification(Info);
}


#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FFireSimulationEditorModule, FireSimulationEditor)
