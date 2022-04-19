// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "CoreMinimal.h"
#include "Upgrade.h"
#include "Blueprint/UserWidget.h"
#include "PPauseWidget.generated.h"

/**
 * 
 */
UCLASS()
class UPGRADE_API UPPauseWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	void NativeConstruct() override;

	UFUNCTION()
		void OnContinueClicked();
	UFUNCTION()
		void OnToTitleClicked();
	UFUNCTION()
		void OnExitClicked();

	UPROPERTY()
		class UButton* BT_close;
	UPROPERTY()
		class UButton* BT_ToTitle;
	UPROPERTY()
		class UButton* BT_Exit;
};
