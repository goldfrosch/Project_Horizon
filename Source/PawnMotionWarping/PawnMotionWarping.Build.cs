using UnrealBuildTool;

public class PawnMotionWarping : ModuleRules
{
	public PawnMotionWarping(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new[]
			{
				"Core"
			}
		);

		PrivateDependencyModuleNames.AddRange(
			new[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore"
			}
		);

		PublicIncludePaths.AddRange(
			new[]
			{
				"PawnMotionWarping/Component"
			}
		);
	}
}