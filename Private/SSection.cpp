// Fill out your copyright notice in the Description page of Project Settings.


#include "SSection.h"
#include "PCharacter.h"
#include "PPlayerController.h"
#include "PGameState.h"
#include "SGameMode.h"

// Sets default values
ASSection::ASSection()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	bNoBattle = false;

	EnemySpawnTime = 2.0f;

}

// Called when the game starts or when spawned
void ASSection::BeginPlay()
{
	Super::BeginPlay();
	setState(bNoBattle ? ESectionState::COMPLETE : ESectionState::READY);
}

void ASSection::setState(ESectionState NewState)
{
	// 일단 상태에 따른 스위치 구문만 설정해놓는다.
	switch (NewState)
	{
	case ESectionState::READY:
	{
		// 플레이어가 다음 업그레이드를 결정하는 단계
		
		break;
	}
	case ESectionState::BATTLE:
	{
		// 플레이어가 업그레이드를 결정하고 시작 버튼을 눌렀을 때 시작하는 단계
		// NPC를 스폰함
		GetWorld()->GetTimerManager().SetTimer(SpawnNPCTimerHandle,
			FTimerDelegate::CreateUObject(this, &ASSection::OnNPCSpawn),
			EnemySpawnTime, false);

		


		break;
	}
	case ESectionState::COMPLETE:
	{
		// NPC를 다 죽이고 난 후
		break;
	}
	}
	CurrentState = NewState;
}

void ASSection::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	setState(bNoBattle ? ESectionState::COMPLETE : ESectionState::READY);
}

void ASSection::OnNPCSpawn()
{
	GetWorld()->SpawnActor<APCharacter>(GetActorLocation() + FVector::UpVector * 88.0f, FRotator::ZeroRotator);
	auto KeyNPC = GetWorld()->SpawnActor<APCharacter>(GetActorLocation() + FVector::UpVector * 88.0f, FRotator::ZeroRotator);
	
	if (KeyNPC != nullptr)
	{
		KeyNPC->OnDestroyed.AddDynamic(this, &ASSection::OnKeyNPCDestroyed);
	}
}

void ASSection::OnKeyNPCDestroyed(AActor* DestroyedActor)
{
	auto Chara = Cast<APCharacter>(DestroyedActor);
	ABCHECK(Chara != nullptr);

	auto CharaCont = Cast<APPlayerController>(Chara->LastHitBy);
	ABCHECK(CharaCont != nullptr);

	auto APGameMode = Cast<ASGameMode>(GetWorld()->GetAuthGameMode());
	ABCHECK(APGameMode != nullptr);
	APGameMode->AddStageNums(CharaCont);



	setState(ESectionState::COMPLETE);
}


//// Called every frame
//void ASSection::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}
//
