// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// #include "CoreMinimal.h"
#include "Upgrade.h"
#include "GameFramework/SaveGame.h"
#include "SSaveGame.generated.h"

// 세이브파일 클래스

/**
 * 
 */
UCLASS()
class UPGRADE_API USSaveGame : public USaveGame
{
	GENERATED_BODY()
public:
	USSaveGame();

	UPROPERTY()
		int32 Level;
	UPROPERTY()
		int32 Exp;
	UPROPERTY()
		FString PlayerName;
};
