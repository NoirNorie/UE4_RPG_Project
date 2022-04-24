// Fill out your copyright notice in the Description page of Project Settings.


#include "PPlayerController.h"
#include "PHudWidget.h"
#include "PPlayerState.h"
#include "PCharacter.h"
#include "PPauseWidget.h"
#include "PUpgradeWidget.h"
#include "PGameOverWidget.h"

APPlayerController::APPlayerController()
{
	static ConstructorHelpers::FClassFinder<UPHudWidget>UI_HUD_C(TEXT("/Game/BPS/Widgets/UI_HUD.UI_HUD_C"));
	if (UI_HUD_C.Succeeded()) HUDWidgetClass = UI_HUD_C.Class;

	static ConstructorHelpers::FClassFinder<UPPauseWidget>UI_Pause_C(TEXT("/Game/BPS/Widgets/UI_PauseMenu.UI_PauseMenu_C"));
	if (UI_Pause_C.Succeeded()) PauseWidgetClass = UI_Pause_C.Class;

	static ConstructorHelpers::FClassFinder<UPUpgradeWidget>UI_UpWidget_C(TEXT("/Game/BPS/Widgets/UI_Upgrade.UI_Upgrade_C"));
	if (UI_UpWidget_C.Succeeded()) UpgradeWidgetClass = UI_UpWidget_C.Class;

	static ConstructorHelpers::FClassFinder<UPGameOverWidget>UI_GameoverUI_C(TEXT("/Game/BPS/Widgets/UI_GameOver.UI_GameOver_C"));
	if (UI_GameoverUI_C.Succeeded()) GameOverWidgetClass = UI_GameoverUI_C.Class;
}

void APPlayerController::BeginPlay()
{
	Super::BeginPlay();

	ChangeInputMode(true);

	//FInputModeGameOnly InputMode;
	//SetInputMode(InputMode);

	HUDWidget = CreateWidget<UPHudWidget>(this, HUDWidgetClass);
	ABCHECK(HUDWidget != nullptr);
	HUDWidget->AddToViewport(1); // 위젯을 화면에 추가하는 함수
	// zorder 디폴트 값은 0

	GameOverWidget = CreateWidget<UPGameOverWidget>(this, GameOverWidgetClass); // 추가만 해놓음
	ABCHECK(GameOverWidget != nullptr);

	UpgradeWidget = CreateWidget<UPUpgradeWidget>(this, UpgradeWidgetClass);
	ABCHECK(UpgradeWidget != nullptr);
	UpgradeWidget->AddToViewport(2);
	//SetPause(true);
	//ChangeInputMode(false); // 업그레이드 선택 중에는 게임 진행을 멈춤
	// ShowUpgradeWidget();

	//auto PState = Cast<APPlayerState>(PlayerState);
	PState = Cast<APPlayerState>(PlayerState);
	ABCHECK(PState != nullptr);
	HUDWidget->BindPlayerState(PState);
	PState->OnPlayerStateChanged.Broadcast();

}

void APPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAction(TEXT("GamePause"), EInputEvent::IE_Pressed, this,
		&APPlayerController::OnGamePause);
}

void APPlayerController::ChangeInputMode(bool bGameMode)
{
	if (bGameMode) // 일반적인 플레이 모드
	{
		SetInputMode(GameInputMode);
		bShowMouseCursor = false; // 마우스는 사용하지 않으므로 가림
	}
	else
	{
		SetInputMode(UIInputMode);
		bShowMouseCursor = true;
	}
}

void APPlayerController::OnGamePause()
{
	PauseWidget = CreateWidget<UPPauseWidget>(this, PauseWidgetClass);
	ABCHECK(PauseWidget != nullptr);
	PauseWidget->AddToViewport(3); // 기존의 위젯들을 덮어쓸 수 있는 위치에 위젯을 배치함 (더 높이 배치함)
	SetPause(true); // 게임 진행을 잠깐 멈춤
	ChangeInputMode(false);
}

void APPlayerController::ShowUpgradeWidget()
{
	UpgradeWidget->AddToViewport(2);
	SetPause(true);
	ChangeInputMode(false); // 업그레이드 선택 중에는 게임 진행을 멈춤
}

void APPlayerController::ShowGameOverUI()
{
	GameOverWidget->AddToViewport();
	ChangeInputMode(false);
}


void APPlayerController::AddStageNums() const
{
	PState->AddStageNums();
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