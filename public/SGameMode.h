// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "CoreMinimal.h"
#include "Upgrade.h"
#include "GameFramework/GameModeBase.h"
#include "SGameMode.generated.h"

/**
 * 
 */
UCLASS()
class UPGRADE_API ASGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	ASGameMode(); // 게임모드 생성자
	virtual void PostLogin(APlayerController* NewPlayer) override;
	// 언리얼에서의 로그인 = 플레이어가 게임에 진입하는 것을 의미
	/*
		PostLogin 진행 과정
		- 플레이어가 조종할 폰을 생성하고, 플레이어 컨트롤러가 해당 폰에 빙의
		- 폰과 플레이어 컨트롤러가 생성되는 시점은 PostInitializeComponents 함수로 파악 가능
		- 빙의를 진행하는 시점은 플레이어 컨트롤러의 Possess, 폰의 PossessdeBy 함수로 파악 가능
	*/

	virtual void PostInitializeComponents() override;
	void AddStageNums(class APPlayerController* StagePlayer);
	int32 GetStage() const;

private:
	UPROPERTY()
		class APGameState* PGameState;


};
