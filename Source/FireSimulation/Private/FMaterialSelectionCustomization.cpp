#include "FMaterialSelectionCustomization.h"
#include "FireSimulationComponent.h"
#include "IDetailCustomization.h"
#include "PropertyEditorModule.h"
#include "DetailLayoutBuilder.h"
#include "DetailCategoryBuilder.h"
#include "DetailWidgetRow.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Input/SComboBox.h"
#include "Modules/ModuleManager.h"
#include <FireSimulationComponent.h>
#include "PropertyCustomizationHelpers.h"
#include "MaterialDataManager.h"


TSharedRef<IDetailCustomization> FMaterialSelectionCustomization::MakeInstance()
{
    return MakeShareable(new FMaterialSelectionCustomization);
}


void FMaterialSelectionCustomization::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
    UE_LOG(LogTemp, Warning, TEXT("CustomizeDetails is being called!"));
    TArray<TWeakObjectPtr<UObject>> ObjectsBeingCustomized;
    DetailBuilder.GetObjectsBeingCustomized(ObjectsBeingCustomized);
    UFireSimulationComponent* FireSimulationComponent = nullptr;

    if (ObjectsBeingCustomized.Num() > 0)
    {
        FireSimulationComponent = Cast<UFireSimulationComponent>(ObjectsBeingCustomized[0].Get());
    }

    if (!FireSimulationComponent) return;
    
    FString SelectedMaterial = FireSimulationComponent->GetSelectedMaterial();

    UE_LOG(LogTemp, Log, TEXT("Initializing OptionsSource."));
    const TArray<TSharedPtr<FString>>& MaterialNames = FMaterialDataManager::Get().GetMaterialNames();
    UE_LOG(LogTemp, Log, TEXT("OptionsSource now contains %d items."), MaterialNames.Num());

    // Найдите индекс выбранного материала
    TSharedPtr<FString> InitialSelectedItem;
    for (const auto& Option : MaterialNames)
    {
        if (*Option == SelectedMaterial)
        {
            InitialSelectedItem = Option;
            break;
        }
    }

    IDetailCategoryBuilder& Category = DetailBuilder.EditCategory("FireSimulation");
    Category.AddCustomRow(FText::FromString("Material Selection"))
        .NameContent()
        [
            SNew(STextBlock).Text(FText::FromString("Selected Material"))
        ]
        .ValueContent()
        .MaxDesiredWidth(250.f)
        [
            SNew(SComboBox<TSharedPtr<FString>>)
                .OptionsSource(&MaterialNames)
                .InitiallySelectedItem(InitialSelectedItem)
                .OnComboBoxOpening_Lambda([]()
                    {
                        UE_LOG(LogTemp, Log, TEXT("ComboBox opening"));
                    })
                .OnGenerateWidget_Lambda([](TSharedPtr<FString> InItem)
                    {
                        return SNew(STextBlock).Text(FText::FromString(*InItem));
                    })
                .OnSelectionChanged_Lambda([FireSimulationComponent](TSharedPtr<FString> NewSelection, ESelectInfo::Type SelectInfo)
                    {
                        if (NewSelection.IsValid())
                        {
                            FireSimulationComponent->UpdateSelectedMaterial(*NewSelection);
                        }
                    })
                        .Content()
                        [
                            SNew(STextBlock)
                                .Text_Lambda([FireSimulationComponent]() -> FText
                                    {
                                        FString CurrentSelectedMaterial = FireSimulationComponent->GetSelectedMaterial();
                                        return FText::FromString(!CurrentSelectedMaterial.IsEmpty() ? CurrentSelectedMaterial : TEXT("Select a Material"));
                                    })
                        ]
        ];
}