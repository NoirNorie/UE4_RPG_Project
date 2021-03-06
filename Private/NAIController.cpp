// Fill out your copyright notice in the Description page of Project Settings.


#include "NAIController.h"
#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperlibrary.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

const FName ANAIController::HomePosKey(TEXT("HomePos"));
const FName ANAIController::PatrolPosKey(TEXT("PatrolPos"));
const FName ANAIController::TargetKey(TEXT("Target"));

ANAIController::ANAIController()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBObject(TEXT(
		"/Game/BPS/AI/BB_AICharacter.BB_AICharacter"));
	if (BBObject.Succeeded()) BBAsset = BBObject.Object;

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT(
		"/Game/BPS/AI/BT_AICharacter.BT_AICharacter"));
	if (BTObject.Succeeded()) BTAsset = BTObject.Object;
}

void ANAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	//if (UseBlackboard(BBAsset, Blackboard))
	//{
	//	Blackboard->SetValueAsVector(HomePosKey, InPawn->GetActorLocation());
	//	if (!RunBehaviorTree(BTAsset))
	//	{
	//		ABLOG(Error, TEXT("AIController couldn't run BT"));
	//	}
	//}
	//GetWorld()->GetTimerManager().SetTimer(RepeatTimerHandle, this, &ANAIController::OnRepeatTimer, RepeatInterval, true);
}

void ANAIController::OnUnPossess()
{
	Super::OnUnPossess();
	//GetWorld()->GetTimerManager().ClearTimer(RepeatTimerHandle);
}

void ANAIController::RunAI()
{
	if (UseBlackboard(BBAsset, Blackboard))
	{
		Blackboard->SetValueAsVector(HomePosKey, GetPawn()->GetActorLocation());
		if (!RunBehaviorTree(BTAsset))
		{
			ABLOG(Error, TEXT("AIController could't run Behavior Tree!"));
		}
	}
}

void ANAIController::StopAI()
{
	auto BTComp = Cast<UBehaviorTreeComponent>(BrainComponent);
	if (BTComp != nullptr) BTComp->StopTree(EBTStopMode::Safe);
}



//void ANAIController::OnRepeatTimer()
//{
//	auto CurrentPawn = GetPawn();
//	ABCHECK(CurrentPawn != nullptr);
//
//	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());
//	// build.cs ????????? NavigationSystem ?????? ????????? ?????????
//	if (NavSystem == nullptr) return; // ????????? ?????? ????????? ?????? ??????
//
//	FNavLocation NextLocation;
//	if (NavSystem->GetRandomPointInNavigableRadius(FVector::ZeroVector, 500.0f, NextLocation))
//	{
//		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, NextLocation.Location);
//		ABLOG(Warning, TEXT("Next Location : %s"), *NextLocation.Location.ToString());
//	}
//}