TSharedRef<IDetailCustomization> FMaterialSelectionCustomization::MakeInstance()
{
    return MakeShareable(new FMaterialSelectionCustomization);
}

void FMaterialSelectionCustomization::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
    // Получение компонента или актора, который мы кастомизируем
    TArray<TWeakObjectPtr<UObject>> ObjectsBeingCustomized;
    DetailBuilder.GetObjectsBeingCustomized(ObjectsBeingCustomized);
    UFireSimulationComponent* Component = nullptr;
    if (ObjectsBeingCustomized.Num() > 0)
    {
        Component = Cast<UFireSimulationComponent>(ObjectsBeingCustomized[0].Get());
    }

    if (!Component)
        return;

    // Предполагаем, что Component->MaterialOptions уже заполнен
    IDetailCategoryBuilder& Category = DetailBuilder.EditCategory("Materials");
    // В CustomizeDetails
    Category.AddCustomRow(FText::FromString("Material Selection"))
    .ValueContent()
    .MaxDesiredWidth(250.f)
    [
        SNew(SComboBox<TSharedPtr<FMaterialData>>)
        .OptionsSource(&Component->MaterialOptions)
        .OnGenerateWidget_Lambda([](TSharedPtr<FMaterialData> MaterialInfo)
        {
            return SNew(STextBlock).Text(FText::FromString(MaterialInfo->Name));
        })
        .OnSelectionChanged_Lambda([Component](TSharedPtr<FMaterialData> NewSelection, ESelectInfo::Type SelectInfo)
        {
            // Обработка выбора материала
        })
        .Content()
        [
            SNew(STextBlock).Text_Lambda([Component]() -> FText
            {
                // Вывод выбранного материала
                return FText::FromString("Select a Material");
            })
        ]
    ];
}

