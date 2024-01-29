// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Guys : ModuleRules
{
	public Guys(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput", "GameplayAbilities" , "MoviePlayer", "UMG", "Slate", "SlateCore", "Niagara" });

		PrivateDependencyModuleNames.AddRange(new string[] { "GameplayAbilities", "GameplayTags", "GameplayTasks" });
	}
}
