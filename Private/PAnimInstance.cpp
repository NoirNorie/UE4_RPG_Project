// Fill out your copyright notice in the Description page of Project Settings.


#include "PAnimInstance.h"
#include "PCharacter.h"
#include "PGameInstance.h"
#include "PCharacterSetting.h" //비동기 로딩용 세팅 헤더

UPAnimInstance::UPAnimInstance()
{
	CurrentPawnSpeed = 0.0f;
	IsInAir = false;
	IsDead = false;

	//static ConstructorHelpers::FObjectFinder<UAnimMontage> Attack_Montage(
	//	TEXT("/Game/PlayerCharacter/Knight/KnightATKMontage.KnightATKMontage"));
	//if (Attack_Montage.Succeeded()) AttackMontage = Attack_Montage.Object;

	static ConstructorHelpers::FObjectFinder<UAnimMontage> Attack_Montage_Hammer(TEXT("/Game/PlayerCharacter/Hammer/HammerATKMontage.HammerATKMontage"));
	if (Attack_Montage_Hammer.Succeeded())
	{
		MontMap.Add(0, Attack_Montage_Hammer.Object);
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> Attack_Montage_2Hand(TEXT("/Game/PlayerCharacter/2Hand/Hand2ATKMontage.Hand2ATKMontage"));
	if (Attack_Montage_2Hand.Succeeded())
	{
		MontMap.Add(1, Attack_Montage_2Hand.Object);
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> Attack_Montage_Knight(TEXT("/Game/PlayerCharacter/Knight/KnightATKMontage.KnightATKMontage"));
	if (Attack_Montage_Knight.Succeeded())
	{
		MontMap.Add(2, Attack_Montage_Knight.Object);
	}
	charaClass = 0;
}

//void UPAnimInstance::NativeBeginPlay()
//{
//	Super::NativeBeginPlay();
//
//	auto PawnGet = TryGetPawnOwner();
//	auto Chara = Cast<APCharacter>(PawnGet);
//	int32 IDX = Chara->GetCharaClass();
//	auto PGameInst = Cast<UPGameInstance>(UPGameInstance::StaticClass());
//	AssetStreamingHandle = PGameInst->StreamableManager.RequestAsyncLoad(CharacterAssetToLoad,
//		FStreamableDelegate::CreateUObject(this, &UPAnimInstance::SetMontageAnim));
//}

//void UPAnimInstance::OnAssetLoadCompleted()
//{
//
//}

void UPAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	auto Pawn = TryGetPawnOwner();
	if (!::IsValid(Pawn)) return; // 폰을 얻어오지 못하는 경우 강제반환한다.
	/*
		엔진은 틱마다 입력 시스템->게임 로직-> 애니메이션 시스템 순으로 로직 실행
		- 플레이어에게 입력을 받고 폰을 움직이게 하고 폰의 최종 움직임과 애니메이션을 연결하는 개념
	*/

	if (!IsDead) // 사망하지 않은 경우에만 처리한다.
	{
		CurrentPawnSpeed = Pawn->GetVelocity().Size();
		auto Character = Cast<ACharacter>(Pawn);
		if (Character)
		{
			IsInAir = Character->GetMovementComponent()->IsFalling();
		}

	}
}

void UPAnimInstance::SetDeadAnim()
{
	IsDead = true;
}


void UPAnimInstance::PlayAttackMontage()
{
	ABCHECK(!IsDead);
	if (!Montage_IsPlaying(AttackMontage))
	{
		Montage_Play(AttackMontage, 1.0f);
	}
}

void UPAnimInstance::JumpToAttackMontageSection(int32 NewSection)
{
	ABCHECK(!IsDead);
	ABCHECK(Montage_IsPlaying(AttackMontage));
	Montage_JumpToSection(GetAttackMontageSectionName(NewSection), AttackMontage);
}


// 노티파이 함수
void UPAnimInstance::AnimNotify_AttackHitCheck()
{
	// ABLOG_S(Warning);
	OnAttackHitCheck.Broadcast();
}

void UPAnimInstance::AnimNotify_NextAttackCheck()
{
	ABLOG_S(Warning);
	ABCHECK(Montage_IsPlaying(AttackMontage));
	OnNextAttackCheck.Broadcast();
}

// 캐릭터 직업에 따라 다른 공격모션을 선택하도록 설정하는 함수
void UPAnimInstance::SetMontageAnim(int32 sel)
{
	AttackMontage = nullptr;
	charaClass = sel;
	UE_LOG(LogTemp, Log, TEXT("Montage Load %d"), sel);
	switch (sel)
	{
	case 0:
	{
		FString path = TEXT("/Game/PlayerCharacter/2Hand/Hand2ATKMontage.Hand2ATKMontage");
		AttackMontage = Cast<UAnimMontage>(StaticLoadObject(UAnimMontage::StaticClass(), NULL, *path));
		ABCHECK(AttackMontage != nullptr);
		break;
	}
	case 1:
	{
		FString path = TEXT("/Game/PlayerCharacter/Hammer/HammerATKMontage.HammerATKMontage");
		AttackMontage = Cast<UAnimMontage>(StaticLoadObject(UAnimMontage::StaticClass(), NULL, *path));
		ABCHECK(AttackMontage != nullptr);
		break;
	}
	case 2:
	{
		FString path = TEXT("/Game/PlayerCharacter/Knight/KnightATKMontage.KnightATKMontage");
		AttackMontage = Cast<UAnimMontage>(StaticLoadObject(UAnimMontage::StaticClass(), NULL, *path));
		ABCHECK(AttackMontage != nullptr);
		break;
	}
	}
}

FName UPAnimInstance::GetAttackMontageSectionName(int32 Section)
{
	ABCHECK(FMath::IsWithinInclusive<int32>(Section, 1, 3), NAME_None);
	return FName(*FString::Printf(TEXT("Attack%d"), Section));
}
