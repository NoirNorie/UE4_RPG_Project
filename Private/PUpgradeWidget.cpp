// Fill out your copyright notice in the Description page of Project Settings.


#include "PUpgradeWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "PCharacterStatComponent.h"
#include "PUpgradeWidgetBT.h"
#include "PPlayerState.h"

void UPUpgradeWidget::BindCharacterStat(class UPCharacterStatComponent* CharacterStat)
{
	ABCHECK(CharacterStat != nullptr);
	CurrentCharacterStat = CharacterStat;
}

void UPUpgradeWidget::BindPlayerState(class APPlayerState* PlayerState)
{
	ABCHECK(PlayerState != nullptr);
	CurrentPlayerState = PlayerState;
}

void UPUpgradeWidget::NativeConstruct()
{
	Super::NativeConstruct();
	TB_Gold = Cast<UTextBlock>(GetWidgetFromName(TEXT("TB_Gold")));
	ABCHECK(TB_Gold != nullptr);
	TB_Stage = Cast<UTextBlock>(GetWidgetFromName(TEXT("TB_Stage")));
	ABCHECK(TB_Stage != nullptr);
	BT_Exit = Cast<UButton>(GetWidgetFromName(TEXT("BT_Exit")));
	ABCHECK(BT_Exit);
	UI_UpgradeBT = Cast<UPUpgradeWidgetBT>(GetWidgetFromName(TEXT("UI_UpgradeBT")));
	ABCHECK(UI_UpgradeBT);
}

void UPUpgradeWidget::UpdateCharacterStat()
{

}

void UPUpgradeWidget::UpdatePlayerState()
{

}