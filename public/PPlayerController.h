// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "CoreMinimal.h"
#include "Upgrade.h"
#include "GameFramework/PlayerController.h"
#include "PPlayerController.generated.h"

// 경험해보니 왠만한 위젯들은 여기에 장착하여 사용하는것이 편함

/**
 * 
 */
UCLASS()
class UPGRADE_API APPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	APPlayerController();

	virtual void PostInitializeComponents() override;
	virtual void OnPossess(APawn* aPawn) override;

	class UPHudWidget* GetHudWidget() const;
	void NPCKill(class APCharacter* KilledNPC) const;
	void AddStageNums() const;

	void ChangeInputMode(bool bGameMode = true);

	void ShowGameOverUI();

	void ShowUpgradeWidget(); // 업그레이드 창을 띄워줄 함수

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
		TSubclassOf<class UPHudWidget> HUDWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
		TSubclassOf<class UPPauseWidget> PauseWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
		TSubclassOf<class UPUpgradeWidget> UpgradeWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
		TSubclassOf<class UPGameOverWidget> GameOverWidgetClass;


private:
	UPROPERTY()
		class UPHudWidget* HUDWidget;
	UPROPERTY()
		class APPlayerState* PState;
	UPROPERTY()
		class UPUpgradeWidget* UpgradeWidget;
	UPROPERTY()
		class UPPauseWidget* PauseWidget;
	UPROPERTY()
		class UPGameOverWidget* GameOverWidget;

	void OnGamePause(); // 게임 일시정지용 함수
	FInputModeGameOnly GameInputMode;
	FInputModeUIOnly UIInputMode;
};
