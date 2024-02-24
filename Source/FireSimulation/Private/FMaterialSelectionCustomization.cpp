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


FMaterialSelectionCustomization::FMaterialSelectionCustomization()
	: MaterialComboBox(nullptr), MaterialNames(FMaterialDataManager::Get().GetMaterialNames())
{
	
}


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
	TSharedPtr<IPropertyHandle> MaterialPropertyHandle = DetailBuilder.GetProperty(GET_MEMBER_NAME_CHECKED(UFireSimulationComponent, SelectedMaterial));

	IDetailCategoryBuilder& Category = DetailBuilder.EditCategory("FireSimulation");
	Category.AddProperty(MaterialPropertyHandle)
		.CustomWidget()
		.NameContent()
		[
			MaterialPropertyHandle->CreatePropertyNameWidget()
		]
		.ValueContent()
		.MaxDesiredWidth(250.f)
		[
			SAssignNew(MaterialComboBox, SComboBox<TSharedPtr<FString>>)
				.OptionsSource(&MaterialNames)
				.OnSelectionChanged_Lambda([FireSimulationComponent](TSharedPtr<FString> NewSelection, ESelectInfo::Type SelectInfo)
					{
						if (NewSelection.IsValid() && FireSimulationComponent && SelectInfo != ESelectInfo::Direct)
						{
							FireSimulationComponent->UpdateSelectedMaterial(*NewSelection);
						}
					})
				.OnGenerateWidget_Lambda([](TSharedPtr<FString> InItem)
					{
						return SNew(STextBlock).Text(FText::FromString(*InItem));
					})
						.Content()
						[
							SNew(STextBlock)
								.Text_Lambda([MaterialPropertyHandle]() -> FText
									{
										FString CurrentSelectedMaterial;
										MaterialPropertyHandle->GetValue(CurrentSelectedMaterial);
										return FText::FromString(!CurrentSelectedMaterial.IsEmpty() ? CurrentSelectedMaterial : TEXT("Select a Material"));
									})
						]
		];
}