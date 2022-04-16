// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "CoreMinimal.h"
#include "Upgrade.h"
#include "Blueprint/UserWidget.h"
#include "STitleWidget.generated.h"

/**
 * 
 */
UCLASS()
class UPGRADE_API USTitleWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;

protected: // 위젯 내부 버튼
	UPROPERTY()
		class UButton* BT_NewGame;
	UPROPERTY()
		class UButton* BT_Continue;
	UPROPERTY()
		class UButton* BT_Exit;
private: // 내부 함수
	UFUNCTION()
		void OnNewGameClicked();
	UFUNCTION()
		void OnContinueClicked();
	UFUNCTION()
		void OnExitClicked();
	
	UPROPERTY()
		class USSaveGame* LoadGame;
};
