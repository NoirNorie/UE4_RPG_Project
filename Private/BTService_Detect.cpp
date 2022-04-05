// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_Detect.h"
#include "NAIController.h"
#include "PCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DrawDebugHelpers.h"

UBTService_Detect::UBTService_Detect()
{
	NodeName = TEXT("Detect");
	Interval = 1.0f;
}

void UBTService_Detect::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (ControllingPawn == nullptr) return;

	UWorld* World = ControllingPawn->GetWorld();
	FVector Center = ControllingPawn->GetActorLocation();
	float DetectRadius = 600.0f;
	if (World == nullptr) return;

	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams CollisionQueryParam(NAME_None, false, ControllingPawn);
	bool bResult = World->OverlapMultiByChannel(
		OverlapResults, Center, FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel1,
		FCollisionShape::MakeSphere(DetectRadius),
		CollisionQueryParam);


	if (bResult) // 무언가 감지 범위 내에 존재한다면
	{
		for (auto const& OverlapResult : OverlapResults)
		{
			APCharacter* PChara = Cast<APCharacter>(OverlapResult.GetActor());
			if (PChara && PChara->GetController()->IsPlayerController()) // 충돌 감지 범위 내에 들어온 캐릭터가 플레이어가 조종하고 있는 캐릭터일 경우에 대해서
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsObject(ANAIController::TargetKey, PChara);
				DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Green, false, 0.2f);
				DrawDebugPoint(World, PChara->GetActorLocation(), 10.0f, FColor::Blue, false, 0.2f);
				return;
			}
		}
	}


	DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Red, false, 0.2f);
}