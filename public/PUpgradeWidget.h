// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "CoreMinimal.h"
#include "Upgrade.h"
#include "Blueprint/UserWidget.h"
#include "PUpgradeWidget.generated.h"

/**
 * 
 */
UCLASS()
class UPGRADE_API UPUpgradeWidget : public UUserWidget
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
		class UTextBlock* TB_Gold;
	UPROPERTY()
		class UTextBlock* TB_Stage;
	UPROPERTY()
		class UButton* BT_Exit;
	UPROPERTY()
		class UButton* BT_LeftSelect;
	UPROPERTY()
		class UButton* BT_RightSelect;
};
