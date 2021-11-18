// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class SideScroller : ModuleRules
{
	public SideScroller(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "Paper2D" });
	}
}
