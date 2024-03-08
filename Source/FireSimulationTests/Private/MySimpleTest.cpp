#include "CoreMinimal.h"
#include "Misc/AutomationTest.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FMySimpleTest, "FireSimulation.FireSimulationTests.MySimpleTest", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FMySimpleTest::RunTest(const FString& Parameters)
{
    // Тестируемая логика здесь
    TestTrue("True должен быть истинным", true);

    // Возвращаем true, если тест прошел успешно
    return true;
}
