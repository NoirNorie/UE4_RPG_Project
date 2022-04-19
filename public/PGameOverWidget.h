// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "CoreMinimal.h"
#include "Upgrade.h"
#include "PPauseWidget.h"
#include "PGameOverWidget.generated.h"

/**
 * 
 */
UCLASS()
class UPGRADE_API UPGameOverWidget : public UPPauseWidget
{
	GENERATED_BODY()
public:
	void BindGameState(class APGameState* GameState);
protected:
	virtual void NativeConstruct() override;
private:
	TWeakObjectPtr<class APGameState> CurrentGameState;
};
