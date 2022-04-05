// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_FindPatrolPos.generated.h"

/**
 * 
 */
UCLASS()
class UPGRADE_API UBTTask_FindPatrolPos : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTask_FindPatrolPos();

	// 작업 수행 함수
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};

/*
	BT는 태스크 수행 시 태스크 클래스의 ExecuteTask 함수를 실행함
	- 4개의 값 중 하나를 반환해야 한다
	1: Aborted: 태스크 수행 중 중단, 결과적으로 수행 실패
	2: Failed: 태스크 수행 실패
	3: Succeeded: 태스크를 성공적으로 수행
	4: InProgress: 태스크 수행 중, 태스크의 수행 결과는 아직 정의되지 않음

	이 결과들로 다음 태스크를 계속 수행할지, 중단할지 결정된다
	- 시퀀스의 경우 태스크 실패 전까지 계속해서 태스크를 수행하는 성질을 갖고 있음
*/