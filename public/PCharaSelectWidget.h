// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "CoreMinimal.h"
#include "Upgrade.h"
#include "Blueprint/UserWidget.h"
#include "PCharaSelectWidget.generated.h"

/**
 * 
 */
UCLASS()
class UPGRADE_API UPCharaSelectWidget : public UUserWidget
{
	GENERATED_BODY()
protected: // 위젯 기능
	UFUNCTION(BlueprintCallable)
		void NextCharacter(bool bForward = true);
	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Character)
		int32 CurrentIDX;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Character)
		int32 MaxIDX;

	void SetSKANIM();

	TWeakObjectPtr<USkeletalMeshComponent> TargetComponent;

protected: // 위젯 내부
	UPROPERTY()
		class UButton* PrevBT;
	UPROPERTY()
		class UButton* NextBT;
	UPROPERTY()
		class UTextBlock* CLASSTB;
	UPROPERTY()
		class UButton* StartBT;

private: // 클릭 함수
	UFUNCTION()
		void OnPrevClicked();
	UFUNCTION()
		void OnNextClicked();
	UFUNCTION()
		void OnStartClicked();
	FText charaName;
};
