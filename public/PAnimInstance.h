// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "CoreMinimal.h"
#include "Upgrade.h"
#include "Animation/AnimInstance.h"
#include "PAnimInstance.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnNextAttackCheckDelegate);
DECLARE_MULTICAST_DELEGATE(FOnAttackHitCheckDelegate);

/**
 * 
 */
UCLASS()
class UPGRADE_API UPAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	UPAnimInstance();
	// virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	void PlayAttackMontage();

	void JumpToAttackMontageSection(int32 NewSection);

	// 델리게이트
	FOnNextAttackCheckDelegate OnNextAttackCheck;
	FOnAttackHitCheckDelegate OnAttackHitCheck;

	void SetMontageAnim(int32 sel); // 애니메이션 몽타주를 선택할 함수
	void SetDeadAnim();

	int32 charaClass;

	// 애니메이션 몽타주
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attack)
		UAnimMontage* AttackMontage;
private:



	// AllowPrivateAccess = true : 프라이빗 접근 허용
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
		float CurrentPawnSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = trie))
		bool IsInAir; // 공중에 있는지 판정할 함수


	// 노티파이
	UFUNCTION()
		void AnimNotify_AttackHitCheck();
	UFUNCTION()
		void AnimNotify_NextAttackCheck();

	FName GetAttackMontageSectionName(int32 Section);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
		bool IsDead;

	FSoftObjectPath CharacterAssetToLoad = FSoftObjectPath(nullptr);
	TSharedPtr<struct FStreamableHandle> AssetStreamingHandle;

	TMap<int32, UAnimMontage*> MontMap;
	bool unload = true;
};
