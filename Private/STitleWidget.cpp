// Fill out your copyright notice in the Description page of Project Settings.


#include "STitleWidget.h"
#include "Components/Button.h"

void USTitleWidget::NativeConstruct()
{
	Super::NativeConstruct();

	BT_NewGame = Cast<UButton>(GetWidgetFromName(TEXT("BT_NewGame")));
	ABCHECK(BT_NewGame != nullptr);
	BT_NewGame->OnClicked.AddDynamic(this, &USTitleWidget::OnNewGameClicked);

	BT_Continue = Cast<UButton>(GetWidgetFromName(TEXT("BT_Continue")));
	ABCHECK(BT_Continue != nullptr);
	BT_Continue->OnClicked.AddDynamic(this, &USTitleWidget::OnContinueClicked);

	BT_Exit = Cast<UButton>(GetWidgetFromName(TEXT("BT_Exit")));
	ABCHECK(BT_Exit != nullptr);
	BT_Exit->OnClicked.AddDynamic(this, &USTitleWidget::OnExitClicked);
}

void USTitleWidget::OnNewGameClicked()
{

}
void USTitleWidget::OnContinueClicked()
{

}
void USTitleWidget::OnExitClicked()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(),
		EQuitPreference::Quit, true);
}