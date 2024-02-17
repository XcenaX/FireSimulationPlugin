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


TSharedRef<IDetailCustomization> FMaterialSelectionCustomization::MakeInstance()
{
    return MakeShareable(new FMaterialSelectionCustomization);
}


void FMaterialSelectionCustomization::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
    TArray<TWeakObjectPtr<UObject>> ObjectsBeingCustomized;
    DetailBuilder.GetObjectsBeingCustomized(ObjectsBeingCustomized);
    UFireSimulationComponent* FireSimulationComponent = nullptr;

    FireSimulationComponent->InitializeMaterialNames();

    if (ObjectsBeingCustomized.Num() > 0)
    {
        FireSimulationComponent = Cast<UFireSimulationComponent>(ObjectsBeingCustomized[0].Get());
    }

    if (!FireSimulationComponent) return;

    // Создание временного массива TSharedPtr<FString> для источника данных SComboBox
    TArray<TSharedPtr<FString>> MaterialNameOptions;
    for (const FString& MaterialName : FireSimulationComponent->MaterialNames)
    {
        MaterialNameOptions.Add(MakeShared<FString>(MaterialName));
    }

    TSharedPtr<FString> SelectedMaterial = MakeShared<FString>(FireSimulationComponent->GetCurrentMaterialName());

    // Получение IDetailCategoryBuilder для добавления пользовательского UI
    IDetailCategoryBuilder& Category = DetailBuilder.EditCategory("FireSimulation");
    Category.AddCustomRow(FText::FromString("Material Selection"))
        .NameContent()
        [
            SNew(STextBlock)
                .Text(FText::FromString("Selected Material"))
        ]
        .ValueContent()
        .MaxDesiredWidth(250.f)
        [
            SNew(SComboBox<TSharedPtr<FString>>)
                .OptionsSource(&MaterialNameOptions)
                .InitiallySelectedItem(SelectedMaterial)
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
                            SNew(STextBlock).Text_Lambda([SelectedMaterial]() -> FText
                                {
                                    return FText::FromString(SelectedMaterial.IsValid() ? *SelectedMaterial : TEXT("Select a Material"));
                                })
                        ]
        ];

    // Следует помнить, что MaterialNameOptions должен существовать до конца скоупа функции CustomizeDetails,
    // поэтому он определен вне лямбда-выражений.
}
