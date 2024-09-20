// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ProjectSP : ModuleRules
{
	public ProjectSP(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicIncludePaths.AddRange(new string[] { "ProjectSP" });

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput","AIModule", "NavigationSystem", "UMG" });
        PrivateDependencyModuleNames.AddRange(new string[] {
            "GameFeatures",
            "GameplayTasks"
        });
    }
}
