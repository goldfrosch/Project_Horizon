// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ProjectHTarget : TargetRules
{
	public ProjectHTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V5;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_5;
		ExtraModuleNames.Add("ProjectH");
		RegisterModulesCreatedByRider();
	}

	private void RegisterModulesCreatedByRider()
	{
		ExtraModuleNames.AddRange(new[] { "PawnMotionWarping" });
	}
}