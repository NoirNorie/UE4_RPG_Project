// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Attack.h"
#include "NAIController.h"
#include "PCharacter.h"

UBTTask_Attack::UBTTask_Attack()
{
	bNotifyTick = true;
	IsAttacking = false;
}

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto Chara = Cast<APCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (Chara == nullptr) return EBTNodeResult::Failed; // 읽힌 값이 없을 경우 강제 반환

	Chara->Attack(); // 공격 명령
	IsAttacking = true; // 공격 상태로 전환
	Chara->OnAttackEnd.AddLambda([this]()->void {
		IsAttacking = false;
	}); // 람다식으로 공격이 종료된 경우 공격 상태를 해제한다.

	return EBTNodeResult::InProgress;
}

void UBTTask_Attack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	if(!IsAttacking) FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
}