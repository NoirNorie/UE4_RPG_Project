// Fill out your copyright notice in the Description page of Project Settings.


#include "SGameMode.h"
// 플레이어 폰 헤더
#include "PPawn.h"
// 플레이어 캐릭터 헤더
#include "PCharacter.h"
// 플레이어 컨트롤러 헤더
#include "PPlayerController.h"
// 플레이어 정보 헤더
#include "PPlayerState.h"
// 게임 상태 헤더
#include "PGameState.h"

ASGameMode::ASGameMode()
{
	//// 기본 폰 지정
	//DefaultPawnClass = APPawn::StaticClass();
	DefaultPawnClass = APCharacter::StaticClass();
	// 기본 컨트롤러 지정
	PlayerControllerClass = APPlayerController::StaticClass();
	// 정보를 얻어올 클래스 지정
	PlayerStateClass = APPlayerState::StaticClass();
	// 게임 상태를 얻어올 클래스 지정
	GameStateClass = APGameState::StaticClass();
}

void ASGameMode::PostLogin(APlayerController* NewPlayer)
{
	// ABLOG(Warning, TEXT("PostLogin Begin"));
	Super::PostLogin(NewPlayer);
	// ABLOG(Warning, TEXT("PostLogin End"));

	auto PState = Cast<APPlayerState>(NewPlayer->PlayerState);
	ABCHECK(PState != nullptr);
	PState->InitPlayerData();
}