// Fill out your copyright notice in the Description page of Project Settings.


#include "PPlayerState.h"
#include "PGameInstance.h"
#include "SSaveGame.h"

APPlayerState::APPlayerState()
{
	CharacterLevel = 1;
	StageNums = 1;
	EXP = 0;
	CharacterIDX = 0;
	SaveSlotName = TEXT("Player1");
}

int32 APPlayerState::GetCharacterLevel() const // 플레이어의 레벨을 표시할 함수
{
	return CharacterLevel;
}
int32 APPlayerState::GetStageNums() const
{
	return StageNums;
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
	EXP = PSaveGame->Exp;
	CharacterIDX = PSaveGame->CharacterIDX;
	SavePlayerData();
}
void APPlayerState::SavePlayerData()
{
	USSaveGame* NewPlayerData = NewObject<USSaveGame>();
	NewPlayerData->PlayerName = GetPlayerName();
	NewPlayerData->Level = CharacterLevel;
	NewPlayerData->Exp = EXP;
	NewPlayerData->CharacterIDX = CharacterIDX;

	if (!UGameplayStatics::SaveGameToSlot(NewPlayerData, SaveSlotName, 0))
	{
		ABLOG(Error, TEXT("SaveGame Error!"));
	}
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
	SavePlayerData();
	return DidLevelUp;
}

void APPlayerState::AddStageNums()
{
	StageNums++;
	OnPlayerStateChanged.Broadcast();
}

void APPlayerState::SetCharacterLevel(int32 NewCharacterLevel)
{
	auto PGameInst = Cast<UPGameInstance>(GetGameInstance());
	ABCHECK(PGameInst != nullptr);

	CurrentStatData = PGameInst->GetPCharacterData(NewCharacterLevel);
	ABCHECK(CurrentStatData != nullptr);

	CharacterLevel = NewCharacterLevel;
}

int32 APPlayerState::GetCharacterIndex() const
{
	return CharacterIDX;
}