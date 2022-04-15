// Fill out your copyright notice in the Description page of Project Settings.


#include "PUIPlayerController.h"
#include "Blueprint/UserWidget.h"

void APUIPlayerController::BeginPlay()
{
	Super::BeginPlay();

	ABCHECK(UIWidgetClass != nullptr);
	UIWidgetInstance = CreateWidget<UUserWidget>(this, UIWidgetClass);
	ABCHECK(UIWidgetInstance != nullptr);
	UIWidgetInstance->AddToViewport();

	FInputModeUIOnly Mode;
	Mode.SetWidgetToFocus(UIWidgetInstance->GetCachedWidget());
	SetInputMode(Mode); // UI만 동작시키도록 함
	bShowMouseCursor = true; // 마우스를 보이게 만듦


}