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
#include "Misc/ConfigCacheIni.h"

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
    AFireGridManager* GridManager = AFireGridManager::GetInstance();

    // Загрузка введенных пользоваталем данных
    FString AssetPath;
    if (GConfig->GetString(
        TEXT("FireSimulationSettings"),
        TEXT("FireParticle"),
        AssetPath,
        GEditorPerProjectIni
    ))
    {
        UObject* Asset = LoadObject<UParticleSystem>(nullptr, *AssetPath);
        
        if (Asset)
        {
            GridManager->SelectedParticleFire = Asset;
        }
    }

    FString LoadedCubesAmount;
    GConfig->GetString(
        TEXT("FireSimulationSettings"),
        TEXT("CubesAmount"),
        LoadedCubesAmount,
        GEditorPerProjectIni
    );

    FString LoadedThreads;
    GConfig->GetString(
        TEXT("FireSimulationSettings"),
        TEXT("Threads"),
        LoadedThreads,
        GEditorPerProjectIni
    );

    FString LoadedFireSize;
    GConfig->GetString(
        TEXT("FireSimulationSettings"),
        TEXT("FireSize"),
        LoadedFireSize,
        GEditorPerProjectIni
    );

    CubesAmountTextBox = SNew(SEditableTextBox)
        .Padding(FMargin(5.0f, 0.0f, 2.5f, 0.0f))
        .HintText(LOCTEXT("CellSizeHint", "Enter size of cell..."));
    ThreadsTextBox = SNew(SEditableTextBox)
        .Padding(FMargin(5.0f, 0.0f, 2.5f, 0.0f))
        .HintText(LOCTEXT("ThreadsHint", "Enter amount of threads to use in fire simulation..."));
    FireSizeTextBox = SNew(SEditableTextBox)
        .Padding(FMargin(5.0f, 0.0f, 2.5f, 0.0f))
        .HintText(LOCTEXT("FireSizeHint", "Enter size of your Fire Particle System for 1 dimension (example: 10 means Particle will have size of box 10 x 10 x 10 )..."));
    PickFireButton = SNew(SButton)
        .VAlign(VAlign_Center)
        .Text(GridManager->SelectedParticleFire
            ? FText::FromName(GridManager->SelectedParticleFire->GetFName())
            : LOCTEXT("PickActorClassButtonText", "Pick Fire Visualisation"))
        .ContentPadding(FMargin(10.0f))
        .OnClicked(FOnClicked::CreateRaw(this, &FFireSimulationEditorModule::OnPickActorClassClicked));
    
    CubesAmountTextBox->SetText(FText::FromString(LoadedCubesAmount));
    ThreadsTextBox->SetText(FText::FromString(LoadedThreads));
    FireSizeTextBox->SetText(FText::FromString(LoadedFireSize));

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
                .Padding(5)
                [
                    FireSizeTextBox.ToSharedRef()
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
                    SNew(SButton)
                        .Text(LOCTEXT("FillActorsButtonText", "Fill Grid with actors"))
                        .ContentPadding(FMargin(10.0f))
                        .OnClicked(FOnClicked::CreateRaw(this, &FFireSimulationEditorModule::OnFillGridClicked))
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

                AFireGridManager* GridManager = AFireGridManager::GetInstance();
                if (GridManager)
                {       
                    GridManager->DrawGrid(true, World, GridActor);                    
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

    FString FireSizeText = FireSizeTextBox->GetText().ToString();
    int32 FireSize = FCString::Atoi(*FireSizeText);

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
            GridManager->InitializeGrid(GridActor, CubesAmount, Threads, FireSize);
            GridManager->PopulateGridWithActors(World, GridActor);
            ShowNotification("Grid was successfully filled with Actors!");

        }
    }   

    GConfig->SetString(
        TEXT("FireSimulationSettings"),
        TEXT("CubesAmount"),
        *CubesAmountText,
        GEditorPerProjectIni
    );

    GConfig->SetString(
        TEXT("FireSimulationSettings"),
        TEXT("Threads"),
        *ThreadsText,
        GEditorPerProjectIni
    );

    GConfig->SetString(
        TEXT("FireSimulationSettings"),
        TEXT("FireSize"),
        *FireSizeText,
        GEditorPerProjectIni
    );

    GConfig->Flush(false, GEditorPerProjectIni);

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
            
            UParticleSystem* SelectedParticleSystem = Cast<UParticleSystem>(SelectedObject);
            GConfig->SetString(
                TEXT("FireSimulationSettings"),
                TEXT("FireParticle"),
                *SelectedParticleSystem->GetPathName(),
                GEditorPerProjectIni
            );

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

void FFireSimulationEditorModule::ShowNotification(FString message) {
    FNotificationInfo Info(FText::FromString(message));
    Info.ExpireDuration = 5.0f;
    FSlateNotificationManager::Get().AddNotification(Info);
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FFireSimulationEditorModule, FireSimulationEditor)
