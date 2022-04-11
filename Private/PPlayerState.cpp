// Fill out your copyright notice in the Description page of Project Settings.


#include "PPlayerState.h"
#include "PGameInstance.h"
#include "SSaveGame.h"

APPlayerState::APPlayerState()
{
	CharacterLevel = 1;
	GameScore = 0;
	EXP = 0;
	SaveSlotName = TEXT("Player1");
}

int32 APPlayerState::GetGameScore() const		 // 플레이어의 점수를 표시할 함수
{
	return GameScore;
}
int32 APPlayerState::GetCharacterLevel() const // 플레이어의 레벨을 표시할 함수
{
	return CharacterLevel;
}
void APPlayerState::InitPlayerData() // 플레이어 데이터를 읽어들일 함수
{
	//SetPlayerName(TEXT("Player"));
	//SetCharacterLevel(5);
	//GameScore = 0;
	//EXP = 0;

	auto PSaveGame = Cast<USSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlotName, 0));
	if (PSaveGame == nullptr) PSaveGame = GetMutableDefault<USSaveGame>(); // 형변환 된 것이 없다면 만들어냄

	SetPlayerName(PSaveGame->PlayerName);
	SetCharacterLevel(PSaveGame->Level);
	GameScore = 0;
	EXP = PSaveGame->Exp;
}

float APPlayerState::GetExpRation() const
{
	if (CurrentStatData->NextExp <= KINDA_SMALL_NUMBER) return 0.0f;

	float Result = (float)(EXP) / (float)(CurrentStatData->NextExp);
	ABLOG(Warning, TEXT("Ration : %f, Current : %d, Next : %d"), Result, EXP, CurrentStatData->NextExp);
	return Result;
}

bool APPlayerState::AddEXP(int32 InComeExp)
{
	if (CurrentStatData->NextExp == -1) return false;

	bool DidLevelUp = false;
	EXP = EXP + InComeExp;
	if (EXP >= CurrentStatData->NextExp)
	{
		EXP -= CurrentStatData->NextExp;
		SetCharacterLevel(CharacterLevel + 1);
		DidLevelUp = true;
	}
	OnPlayerStateChanged.Broadcast();
	return DidLevelUp;
}

void APPlayerState::SetCharacterLevel(int32 NewCharacterLevel)
{
	auto PGameInst = Cast<UPGameInstance>(GetGameInstance());
	ABCHECK(PGameInst != nullptr);

	CurrentStatData = PGameInst->GetPCharacterData(NewCharacterLevel);
	ABCHECK(CurrentStatData != nullptr);

	CharacterLevel = NewCharacterLevel;
}