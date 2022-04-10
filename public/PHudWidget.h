// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "CoreMinimal.h"
#include "Upgrade.h"
#include "Blueprint/UserWidget.h"
#include "PHudWidget.generated.h"

/**
 * 
 */
UCLASS()
class UPGRADE_API UPHudWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void BindCharacterStat(class UPCharacterStatComponent* CharacterStat);
	void BindPlayerState(class APPlayerState* PlayerState);

protected:
	virtual void NativeConstruct() override;
	void UpdateCharacterStat();
	void UpdatePlayerState();

private:
	TWeakObjectPtr<class UPCharacterStatComponent> CurrentCharacterStat;
	TWeakObjectPtr<class APPlayerState> CurrentPlayerState;

	UPROPERTY()
		class UProgressBar* HPBar;
	UPROPERTY()
		class UProgressBar* ExpBar;
	UPROPERTY()
		class UProgressBar* MPBar;
	UPROPERTY()
		class  UTextBlock* PlayerName;
	UPROPERTY()
		class UTextBlock* PlayerLevel;
};
