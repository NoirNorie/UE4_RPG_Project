// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "CoreMinimal.h"
#include "Upgrade.h"
#include "GameFramework/GameStateBase.h"
#include "PGameState.generated.h"

/**
 * 
 */
UCLASS()
class UPGRADE_API APGameState : public AGameStateBase
{
	GENERATED_BODY()
public:
	APGameState();

	int32 GetTotalStage() const;
	void AddStageNums();

	void SetGameOver();
	bool IsGameOver() const;

private:
	UPROPERTY(Transient)
		int32 TotalStageNums;

	UPROPERTY(Transient)
		bool bGameOver;
};
