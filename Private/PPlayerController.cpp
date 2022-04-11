// Fill out your copyright notice in the Description page of Project Settings.


#include "PPlayerController.h"
#include "PHudWidget.h"
#include "PPlayerState.h"
#include "PCharacter.h"

APPlayerController::APPlayerController()
{
	static ConstructorHelpers::FClassFinder<UPHudWidget>UI_HUD_C(TEXT("/Game/BPS/Widgets/UI_HUD.UI_HUD_C"));
	if (UI_HUD_C.Succeeded())
	{
		HUDWidgetClass = UI_HUD_C.Class;
	}
}

void APPlayerController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeGameOnly InputMode;
	SetInputMode(InputMode);

	HUDWidget = CreateWidget<UPHudWidget>(this, HUDWidgetClass);
	HUDWidget->AddToViewport(); // 위젯을 화면에 추가하는 함수


	//auto PState = Cast<APPlayerState>(PlayerState);
	PState = Cast<APPlayerState>(PlayerState);
	ABCHECK(PState != nullptr);
	HUDWidget->BindPlayerState(PState);
	PState->OnPlayerStateChanged.Broadcast();

}

UPHudWidget* APPlayerController::GetHudWidget() const
{
	return HUDWidget;
}

void APPlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	ABLOG_S(Warning);
}

void APPlayerController::OnPossess(APawn* aPawn)
{
	ABLOG_S(Warning);
	Super::OnPossess(aPawn);
}

void APPlayerController::NPCKill(APCharacter* KilledNPC) const
{
	PState->AddEXP(KilledNPC->GetExp());
}