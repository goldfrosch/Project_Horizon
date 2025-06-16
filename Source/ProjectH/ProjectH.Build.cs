using UnrealBuildTool;

public class ProjectH : ModuleRules
{
	public ProjectH(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new[]
		{
			"Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput"
		});

		PrivateDependencyModuleNames.AddRange(new[]
		{
			"GameplayAbilities", "GameplayTags", "GameplayTasks",
			"OnlineSubsystem", "OnlineSubsystemNull",
			"OnlineSubsystemSteam", "OnlineSubsystemUtils",
			"UMG", "Slate", "SlateCore", "MovieScene",
			"LevelSequence", "MovieSceneTracks", "CableComponent", "Niagara",
			"AIModule"
		});
	}
}