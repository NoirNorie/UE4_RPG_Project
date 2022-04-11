// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "CoreMinimal.h"
#include "Upgrade.h"
#include "GameFramework/PlayerState.h"
#include "PPlayerState.generated.h"

/*
	게임의 진행 상황을 기록할 클래스
*/

DECLARE_MULTICAST_DELEGATE(FOnPlayerStateChangedDelegate);


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

	float GetExpRation() const;
	bool AddEXP(int32 IncomeEXP);


	FOnPlayerStateChangedDelegate OnPlayerStateChanged;

protected:
	UPROPERTY(Transient)
		int32 GameScore;
	UPROPERTY(Transient)
		int32 CharacterLevel;

	UPROPERTY(Transient)
		int32 EXP;
private:
	void SetCharacterLevel(int32 NewCharacterLevel);
	struct FPCharacterData* CurrentStatData;
};
