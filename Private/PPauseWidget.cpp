// Fill out your copyright notice in the Description page of Project Settings.


#include "PPauseWidget.h"
#include "Components/Button.h"
#include "PPlayerController.h"

void UPPauseWidget::NativeConstruct()
{
	Super::NativeConstruct();

	BT_close = Cast<UButton>(GetWidgetFromName(TEXT("BT_close")));
	if (BT_close != nullptr) BT_close->OnClicked.AddDynamic(this, &UPPauseWidget::OnContinueClicked);

	BT_ToTitle = Cast<UButton>(GetWidgetFromName(TEXT("BT_ToTitle")));
	if (BT_ToTitle != nullptr) BT_ToTitle->OnClicked.AddDynamic(this, &UPPauseWidget::OnToTitleClicked);

	BT_Exit = Cast<UButton>(GetWidgetFromName(TEXT("BT_Exit")));
	if (BT_Exit != nullptr) BT_Exit->OnClicked.AddDynamic(this, &UPPauseWidget::OnExitClicked);
}

void UPPauseWidget::OnContinueClicked()
{
	auto PCont = Cast<APPlayerController>(GetOwningPlayer());
	ABCHECK(PCont != nullptr);
	RemoveFromParent();

	PCont->ChangeInputMode(true);
	PCont->SetPause(false);
}

void UPPauseWidget::OnToTitleClicked()
{
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("Title"));
}

void UPPauseWidget::OnExitClicked()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(),
		EQuitPreference::Quit, true);
}