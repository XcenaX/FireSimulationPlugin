using UnrealBuildTool;

public class FireSimulationEditorModule : ModuleRules
{
    public FireSimulationEditorModule(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
        
        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "FireSimulation"
                // Другие зависимости модулей...
            }
            );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore",
                "UnrealEd",
                "EditorStyle"
                // Важно для модулей редактора
                // Другие зависимости модулей...
            }
            );

        // Если вы используете сторонние библиотеки, добавьте их здесь...
    }
}
