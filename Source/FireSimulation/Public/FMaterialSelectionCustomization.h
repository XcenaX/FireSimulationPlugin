#pragma once

#include "IDetailCustomization.h"

class FIRESIMULATION_API FMaterialSelectionCustomization : public IDetailCustomization
{
public:
    FMaterialSelectionCustomization();
    static TSharedRef<IDetailCustomization> MakeInstance();

    virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;

private:
    // ComboBox widget for selecting materials
    TSharedPtr<SComboBox<TSharedPtr<FString>>> MaterialComboBox;
    // List of available material names
    const TArray<TSharedPtr<FString>>& MaterialNames;
};
