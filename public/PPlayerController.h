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

protected:
	virtual void BeginPlay() override;
	// virtual void SetupInputComponent() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
		TSubclassOf<class UPHudWidget> HUDWidgetClass;
private:
	UPROPERTY()
		class UPHudWidget* HUDWidget;
};
