// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class CharacterLimbs : ModuleRules
{
	public CharacterLimbs(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
		
		PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
        
		PrivateIncludePaths.AddRange(new string[] { Name });
	}
}
