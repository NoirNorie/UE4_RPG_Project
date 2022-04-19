// Fill out your copyright notice in the Description page of Project Settings.


#include "PGameOverWidget.h"
#include "Components/Button.h"
#include "PGameState.h"

void UPGameOverWidget::NativeConstruct()
{
	Super::NativeConstruct();
	ABCHECK(CurrentGameState.IsValid());


}

void UPGameOverWidget::BindGameState(class APGameState* GameState)
{
	ABCHECK(GameState != nullptr);
	CurrentGameState = GameState;
}