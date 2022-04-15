// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "CoreMinimal.h"
#include "Upgrade.h"
#include "Blueprint/UserWidget.h"
#include "PUpgradeWidgetBT.generated.h"

/**
 * 
 */
UCLASS()
class UPGRADE_API UPUpgradeWidgetBT : public UUserWidget
{
	GENERATED_BODY()
public:
	void ApplyUpgrade();
protected:
	virtual void NativeConstruct() override;

private:

	UPROPERTY()
		class UButton* BT_Right;
	UPROPERTY()
		class UImage* IG_RightImg;
	UPROPERTY()
		class UTextBlock* TB_RightEX;
	UPROPERTY()
		class UButton* BT_Left;
	UPROPERTY()
		class UImage* IG_LeftImg;
	UPROPERTY()
		class UTextBlock* TB_LeftEX;

};
