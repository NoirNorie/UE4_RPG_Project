// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "CoreMinimal.h"
#include "Upgrade.h"
#include "GameFramework/PlayerController.h"
#include "PUIPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class UPGRADE_API APUIPlayerController : public APlayerController
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
		TSubclassOf<class UUserWidget> UIWidgetClass;
	UPROPERTY()
		class UUserWidget* UIWidgetInstance;
	
};
