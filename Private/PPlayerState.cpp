// Fill out your copyright notice in the Description page of Project Settings.


#include "PPlayerState.h"

APPlayerState::APPlayerState()
{
	CharacterLevel = 1;
	GameScore = 0;
}

int32 APPlayerState::GetGameScore() const		 // 플레이어의 점수를 표시할 함수
{
	return GameScore;
}
int32 APPlayerState::GetCharacterLevel() const // 플레이어의 레벨을 표시할 함수
{
	return CharacterLevel;
}
void APPlayerState::InitPlayerData()
{
	SetPlayerName(TEXT("AAA"));
	CharacterLevel = 5;
	GameScore = 0;
}