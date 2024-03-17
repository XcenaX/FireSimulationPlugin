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
    CubesAmountTextBox = SNew(SEditableTextBox)
        .Padding(FMargin(5.0f, 0.0f, 2.5f, 0.0f))
        .HintText(LOCTEXT("CellSizeHint", "Enter amount of cubes in 1 dimension..."));
    ThreadsTextBox = SNew(SEditableTextBox)
        .Padding(FMargin(5.0f, 0.0f, 2.5f, 0.0f))
        .HintText(LOCTEXT("ThreadsHint", "Enter amount of threads to use in fire simulation..."));
    PickFireButton = SNew(SButton)
        .VAlign(VAlign_Center)
        .Text(AFireGridManager::GetInstance()->SelectedParticleFire != nullptr
            ? FText::FromName(AFireGridManager::GetInstance()->SelectedParticleFire->GetFName())
            : LOCTEXT("PickActorClassButtonText", "Pick Fire Visualisation"))
        .ContentPadding(FMargin(10.0f))
        .OnClicked(FOnClicked::CreateRaw(this, &FFireSimulationEditorModule::OnPickActorClassClicked));
    PickFogButton = SNew(SButton)
        .VAlign(VAlign_Center)
        .Text(AFireGridManager::GetInstance()->SelectedParticleFog != nullptr
            ? FText::FromName(AFireGridManager::GetInstance()->SelectedParticleFog->GetFName())
            : LOCTEXT("PickFogClassButtonText", "Pick Fog Visualisation"))
        .ContentPadding(FMargin(10.0f))
        .OnClicked(FOnClicked::CreateRaw(this, &FFireSimulationEditorModule::OnPickFogClassClicked));


    return SNew(SDockTab)
        .TabRole(ETabRole::NomadTab)
        [
            SNew(SVerticalBox)
                + SVerticalBox::Slot()                
                .Padding(5)
                [
                    SNew(STextBlock)
                        .Text(LOCTEXT("FireGridManagerTab", "Fire Grid Manager"))
                ]
                + SVerticalBox::Slot()
                .Padding(5)
                [
                    CubesAmountTextBox.ToSharedRef()
                ]
                + SVerticalBox::Slot()                
                .Padding(5)
                [
                    ThreadsTextBox.ToSharedRef()
                ]
                + SVerticalBox::Slot()
                .AutoHeight()
                .Padding(5)
                [
                    PickFireButton.ToSharedRef()
                ]
                + SVerticalBox::Slot()
                .AutoHeight()
                .Padding(5)
                [
                    SNew(SHorizontalBox)
                        + SHorizontalBox::Slot()
                        .FillWidth(0.45)
                        .Padding(FMargin(2.5f, 0.0f, 5.0f, 0.0f))
                        [
                            SNew(SButton)
                                .Text(LOCTEXT("InitializeButtonText", "Draw Grid"))
                                .ContentPadding(FMargin(10.0f))
                                .OnClicked(FOnClicked::CreateRaw(this, &FFireSimulationEditorModule::OnInitializeGridClicked))
                        ]
                        + SHorizontalBox::Slot()
                        .FillWidth(0.45)
                        .Padding(FMargin(5.0f, 0.0f, 2.5f, 0.0f))
                        [
                            SNew(SButton)
                                .Text(LOCTEXT("ClearButtonText", "Clear Grid"))
                                .ContentPadding(FMargin(10.0f))
                                .OnClicked(FOnClicked::CreateRaw(this, &FFireSimulationEditorModule::OnClearGridClicked))
                        ]
                ]
                + SVerticalBox::Slot()
                .AutoHeight()
                .Padding(5)
                [
                    SNew(SButton)
                        .Text(LOCTEXT("FillActorsButtonText", "Fill Grid with actors"))
                        .ContentPadding(FMargin(10.0f))
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

                AFireGridManager* GridManager = AFireGridManager::GetInstance();
                if (GridManager)
                {       
                    if (CubesAmount > 40) {
                        ShowNotification("Drawing a grid with so many cells can take up a lot of resources! Operation cancelled!");
                    }
                    else {
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

    AFireGridManager* GridManager = AFireGridManager::GetInstance();
    if (GridManager && CubesAmount > 0)
    {
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
    }   
    return FReply::Handled();
}

FReply FFireSimulationEditorModule::OnPickActorClassClicked()
{
    // Настройка конфигурации пикера ассетов
    FAssetPickerConfig AssetPickerConfig;
    AssetPickerConfig.Filter.ClassNames.Add(UParticleSystem::StaticClass()->GetFName());
    AssetPickerConfig.OnAssetSelected = FOnAssetSelected::CreateLambda([this](const FAssetData& AssetData)
        {
            UObject* SelectedObject = AssetData.GetAsset();
            AFireGridManager::GetInstance()->SelectedParticleFire = SelectedObject;

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


FReply FFireSimulationEditorModule::OnPickFogClassClicked()
{
    // Настройка конфигурации пикера ассетов
    FAssetPickerConfig AssetPickerConfig;
    AssetPickerConfig.Filter.ClassNames.Add(UParticleSystem::StaticClass()->GetFName());
    AssetPickerConfig.OnAssetSelected = FOnAssetSelected::CreateLambda([this](const FAssetData& AssetData)
        {
            UObject* SelectedObject = AssetData.GetAsset();
            AFireGridManager::GetInstance()->SelectedParticleFog = SelectedObject;

            ShowNotification("Fog Visualisation was picked!");
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
        .Title(FText::FromString("Pick Fog visualisation"))
        .ClientSize(FVector2D(600, 500))
        [
            AssetPicker
        ];

    FSlateApplication::Get().AddModalWindow(PickerWindow, nullptr, false);


    return FReply::Handled();
}

void FFireSimulationEditorModule::ShowNotification(FString message) {
    FNotificationInfo Info(FText::FromString(message));
    Info.ExpireDuration = 5.0f;
    FSlateNotificationManager::Get().AddNotification(Info);
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FFireSimulationEditorModule, FireSimulationEditor)
