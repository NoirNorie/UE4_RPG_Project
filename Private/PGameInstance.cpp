// Fill out your copyright notice in the Description page of Project Settings.


#include "PGameInstance.h"

UPGameInstance::UPGameInstance()
{
	FString CharacterDataPath = TEXT("DataTable'/Game/GameData/PCharacterData.PCharacterData'"); // 데이터 테이블을 가져온다
	
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_Character(*CharacterDataPath);
	ABCHECK(DT_Character.Succeeded());
	PCharacterTable = DT_Character.Object;
	ABCHECK(PCharacterTable->GetRowMap().Num() > 0);
}

void UPGameInstance::Init()
{
	Super::Init();
	// ABLOG(Warning, TEXT("DropExp of Level 20 PCharacter : %d"), GetPCharacterData(20)->DropExp);
}

/*
	게임이 시작되는 과정
	- 1: 게임 앱의 초기화				= UGameInstance::Init() 함수
	- 2: 레벨에 속한 액터의 초기화		= AActor::PostInitializeComponents() 함수
	- 3: 플레이어의 로그인				= AGameMode::PostLogin() 함수
	- 4: 게임의 시작					= AGameMode::StartPlay() 함수, AActor::BeginPlay() 함수
*/


FPCharacterData* UPGameInstance::GetPCharacterData(int32 Level)
{
	return PCharacterTable->FindRow<FPCharacterData>(*FString::FromInt(Level), TEXT(""));
}