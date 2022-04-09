// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "CoreMinimal.h"
#include "Upgrade.h"
#include "GameFramework/PlayerState.h"
#include "PPlayerState.generated.h"

/*
	게임의 진행 상황을 기록할 클래스
*/

/**
 * 
 */
UCLASS()
class UPGRADE_API APPlayerState : public APlayerState
{
	GENERATED_BODY()
public:
	APPlayerState();

	int32 GetGameScore() const;		 // 플레이어의 점수를 표시할 함수
	int32 GetCharacterLevel() const; // 플레이어의 레벨을 표시할 함수

	void InitPlayerData();

protected:
	UPROPERTY(Transient)
		int32 GameScore;
	UPROPERTY(Transient)
		int32 CharacterLevel;
};