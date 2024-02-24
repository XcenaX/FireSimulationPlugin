#pragma once

#include "IDetailCustomization.h"

class FIRESIMULATION_API FMaterialSelectionCustomization : public IDetailCustomization
{
public:
    FMaterialSelectionCustomization();
    static TSharedRef<IDetailCustomization> MakeInstance();

    virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;

private:
    TSharedPtr<SComboBox<TSharedPtr<FString>>> MaterialComboBox;
    const TArray<TSharedPtr<FString>>& MaterialNames;
};
