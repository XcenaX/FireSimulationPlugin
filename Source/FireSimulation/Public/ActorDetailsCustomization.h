#pragma once

#include "CoreMinimal.h"
#include "IDetailCustomization.h"

class FMyActorDetailsCustomization : public IDetailCustomization
{
public:
    // Фабрика для создания экземпляра класса
    static TSharedRef<IDetailCustomization> MakeInstance();

    // Основная функция настройки панели свойств
    virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;
};
