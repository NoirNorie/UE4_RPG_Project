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

	// int32 GetGameScore() const;		 // 플레이어의 점수를 표시할 함수
	int32 GetCharacterLevel() const; // 플레이어의 레벨을 표시할 함수
	int32 GetStageNums() const;		 // 플레이어의 스테이지를 가져올 함수
	int32 GetCharacterIndex() const;  // 플레이어의 직업을 가져올 함수

	void InitPlayerData(); // 플레이어 데이터 초기화
	void SavePlayerData(); // 플레이어 데이터 저장

	float GetExpRation() const;
	bool AddEXP(int32 IncomeEXP);
	void AddStageNums();

	FString SaveSlotName; // 세이브 슬롯 이름

	FOnPlayerStateChangedDelegate OnPlayerStateChanged;

protected:
	UPROPERTY(Transient)
		int32 CharacterLevel;

	UPROPERTY(Transient)
		int32 EXP;
	UPROPERTY(Transient)
		int32 StageNums; // 현재 스테이지
	UPROPERTY(Transient)
		int32 CharacterIDX;
	
private:
	void SetCharacterLevel(int32 NewCharacterLevel);
	struct FPCharacterData* CurrentStatData;
};
