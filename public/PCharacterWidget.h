// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "CoreMinimal.h"
#include "Upgrade.h"
#include "Blueprint/UserWidget.h"
#include "PCharacterWidget.generated.h"

/**
 * 
 */
UCLASS()
class UPGRADE_API UPCharacterWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void BindCharacterStat(class UPCharacterStatComponent* NewCharacterStat);

protected:
	virtual void NativeConstruct() override;
	void UpdateHPWidget();


private:
	TWeakObjectPtr<class UPCharacterStatComponent> CurrentCharacterStat;

	UPROPERTY()
		class UProgressBar* HPProgressBar;
};
