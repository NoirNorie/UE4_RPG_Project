// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "CoreMinimal.h"
#include "Upgrade.h"
#include "GameFramework/PlayerController.h"
#include "PPlayerController.generated.h"

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

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
		TSubclassOf<class UPHudWidget> HUDWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
		TSubclassOf<class UPPauseWidget> PauseWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
		TSubclassOf<class UPGameOverWidget> GameOverWidgetClass;

private:
	UPROPERTY()
		class UPHudWidget* HUDWidget;
	UPROPERTY()
		class APPlayerState* PState;
	UPROPERTY()
		class UPPauseWidget* PauseWidget;
	UPROPERTY()
		class UPGameOverWidget* GameOverWidget;

	void OnGamePause(); // 게임 일시정지용 함수
	FInputModeGameOnly GameInputMode;
	FInputModeUIOnly UIInputMode;
};
