// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_TurnToTarget.h"
#include "NAIController.h"
#include "PCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_TurnToTarget::UBTTask_TurnToTarget()
{
	NodeName = TEXT("Turn");
}

EBTNodeResult::Type UBTTask_TurnToTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto Chara = Cast<APCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (Chara == nullptr) return EBTNodeResult::Failed; // 캐스팅 실패 시 반환

	auto Target = Cast<APCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(ANAIController::TargetKey));
	if (Target == nullptr) return EBTNodeResult::Failed; // 목표를 찾는 것에 실패했을 경우 반환

	// 플레이어 방향을 바라보게 만드는 작업
	FVector LookVector = Target->GetActorLocation() - Chara->GetActorLocation();
	LookVector.Z = 0.0f; // 플레이어와 AI는 같은 평면에 존재하므로 Z값은 무시할 수 있다.
	FRotator TargetRot = FRotationMatrix::MakeFromX(LookVector).Rotator();
	Chara->SetActorRotation(FMath::RInterpTo(Chara->GetActorRotation(), TargetRot, GetWorld()->GetDeltaSeconds(), 2.0f));
	// 바로 캐릭터 방향을 보는 것이 아니라 RInterpTo 함수를 통한 보간을 통해 캐릭터 방향으로 전환하는 것처럼 표현한다.

	return EBTNodeResult::Succeeded; // 여기까지 진행되었다면 성공한 것
}
