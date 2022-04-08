// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "CoreMinimal.h"
#include "Upgrade.h"
#include "AIController.h"
#include "NAIController.generated.h"

/**
 * 
 */
UCLASS()
class UPGRADE_API ANAIController : public AAIController
{
	GENERATED_BODY()
public:
	ANAIController();
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

	// 4.21 버전부터인가 Possess, UnPossess 함수를 사용할 수 없게 됨(final로 상속 받지 못함)
	// OnPossess, OnUnPossess 함수가 기능은 동일하다고 하니 이 쪽을 사용하면 됨
	
	static const FName HomePosKey;
	static const FName PatrolPosKey;
	static const FName TargetKey;

	// 비헤이비어 트리를 수동으로 키고 끌 수 있도록 하는 함수
	void RunAI();
	void StopAI();

private:
	//void OnRepeatTimer();

	//FTimerHandle RepeatTimerHandle;
	//float RepeatInterval;

	UPROPERTY()
		class UBehaviorTree* BTAsset;
	UPROPERTY()
		class UBlackboardData* BBAsset;
};
