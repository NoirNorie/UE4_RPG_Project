// Fill out your copyright notice in the Description page of Project Settings.


#include "PGameState.h"

APGameState::APGameState()
{
	TotalStageNums = 0;
}

int32 APGameState::GetTotalStage() const
{
	return TotalStageNums;
}
void APGameState::AddStageNums()
{
	TotalStageNums++;
}