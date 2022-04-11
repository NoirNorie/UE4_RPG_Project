// Fill out your copyright notice in the Description page of Project Settings.


#include "PHudWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "PCharacterStatComponent.h"
#include "PPlayerState.h"

void UPHudWidget::BindCharacterStat(UPCharacterStatComponent* CharacterStat)
{
	ABCHECK(CharacterStat != nullptr);
	CurrentCharacterStat = CharacterStat;
	CharacterStat->OnHPChanged.AddUObject(this, &UPHudWidget::UpdateCharacterStat);
}

void UPHudWidget::BindPlayerState(APPlayerState* PlayerState)
{
	ABCHECK(PlayerState != nullptr);
	CurrentPlayerState = PlayerState;
	PlayerState->OnPlayerStateChanged.AddUObject(this, &UPHudWidget::UpdatePlayerState);
}

void UPHudWidget::NativeConstruct()
{
	Super::NativeConstruct();
	HPBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("pbHP")));
	ABCHECK(HPBar != nullptr);

	ExpBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("pbEXP")));
	ABCHECK(ExpBar != nullptr);

	MPBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("pbMP")));
	ABCHECK(MPBar != nullptr);

	PlayerName = Cast<UTextBlock>(GetWidgetFromName(TEXT("PlayerCLASS")));
	ABCHECK(PlayerName != nullptr);

	PlayerLevel = Cast<UTextBlock>(GetWidgetFromName(TEXT("PlayerLV")));
	ABCHECK(PlayerLevel != nullptr);
}

void UPHudWidget::UpdateCharacterStat()
{
	ABCHECK(CurrentCharacterStat.IsValid());
	HPBar->SetPercent(CurrentCharacterStat->GetHPRatio());
}

void UPHudWidget::UpdatePlayerState()
{
	ABCHECK(CurrentPlayerState.IsValid());

	ExpBar->SetPercent(CurrentPlayerState->GetExpRation());

	PlayerName->SetText(FText::FromString(CurrentPlayerState->GetPlayerName()));
	PlayerLevel->SetText(FText::FromString(FString::FromInt(CurrentPlayerState->GetCharacterLevel())));


}