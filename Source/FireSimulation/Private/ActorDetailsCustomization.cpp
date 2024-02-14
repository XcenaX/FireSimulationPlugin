#include "MyActorDetailsCustomization.h"
#include "DetailLayoutBuilder.h"
#include "DetailCategoryBuilder.h"
#include "DetailWidgetRow.h"
#include "Widgets/Text/STextBlock.h"

TSharedRef<IDetailCustomization> FMyActorDetailsCustomization::MakeInstance()
{
    return MakeShareable(new FMyActorDetailsCustomization());
}

void FMyActorDetailsCustomization::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
    // Пример добавления текста в панель свойств
    IDetailCategoryBuilder& Category = DetailBuilder.EditCategory("Custom Category");
    Category.AddCustomRow(FText::FromString("Custom Text"))
    .ValueContent()
    [
        SNew(STextBlock).Text(FText::FromString("Hello, World!"))
    ];
}
