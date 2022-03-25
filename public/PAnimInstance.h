// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "CoreMinimal.h"
#include "Upgrade.h"
#include "Animation/AnimInstance.h"
#include "PAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class UPGRADE_API UPAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	UPAnimInstance();
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
private:
	// AllowPrivateAccess = true : 프라이빗 접근 허용
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
		float CurrentPawnSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = trie))
		bool IsInAir; // 공중에 있는지 판정할 함수
};
