// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Upgrade : ModuleRules
{
	public Upgrade(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", 
			"InputCore", "UMG", "AIModule", "NavigationSystem", "GameplayTasks" });

		PrivateDependencyModuleNames.AddRange(new string[] {"UpgradeSetting"  });
		// UpgradeSetting에서 캐릭터 애셋 목록을 얻어올 수 있도록 참조할 모듈 목록을 추가한다
		// private 에서만 사용할 모듈들은 아래, public/private 둘 다 사용할 경우 위에 추가하면 됨


		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
