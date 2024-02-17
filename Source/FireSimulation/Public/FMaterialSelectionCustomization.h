#pragma once

#include "IDetailCustomization.h"

class FIRESIMULATION_API FMaterialSelectionCustomization : public IDetailCustomization
{
public:
    static TSharedRef<IDetailCustomization> MakeInstance();

    virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;

    TArray<TSharedPtr<int32>> MaterialIndices;
};
