// Fill out your copyright notice in the Description page of Project Settings.


#include "PCharacterStatComponent.h"
#include "PGameInstance.h"

// Sets default values for this component's properties
UPCharacterStatComponent::UPCharacterStatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;

	Level = 1;

	// ...
}


// Called when the game starts
void UPCharacterStatComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UPCharacterStatComponent::InitializeComponent()
{
	Super::InitializeComponent();
	
	SetNewLevel(Level);
}

void UPCharacterStatComponent::SetNewLevel(int32 NewLevel)
{
	auto PGInstance = Cast<UPGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	ABCHECK(nullptr != PGInstance);
	CurrentStatData = PGInstance->GetPCharacterData(NewLevel);
	if (CurrentStatData != nullptr)
	{
		Level = NewLevel;
		SetHP(CurrentStatData->MaxHP);
		// CurrentHP = CurrentStatData->MaxHP;
	}
	else
	{
		ABLOG(Error, TEXT("Level (%d) data Doesn't exist"), NewLevel);
	}

}

// 데미지 처리를 수행할 함수
void UPCharacterStatComponent::SetDamage(float NewDamage)
{
	ABCHECK(nullptr != CurrentStatData);
	SetHP(FMath::Clamp<float>(CurrentHP - NewDamage, 0.0f, CurrentStatData->MaxHP));
}

// HP 조정에 사용하는 함수
void UPCharacterStatComponent::SetHP(float NewHP)
{
	CurrentHP = NewHP;
	OnHPChanged.Broadcast();
	if (CurrentHP < KINDA_SMALL_NUMBER) // KINDA_SMALL_NUMBER: 무시 가능한, 미세한 범위의 오차 측정용 매크로
	{
		CurrentHP = 0.0f;
		OnHPIsZero.Broadcast();
	}
}


float UPCharacterStatComponent::GetAttack()
{
	ABCHECK(nullptr != CurrentStatData, 0.0f);
	return CurrentStatData->Attack;
}

float UPCharacterStatComponent::GetHPRatio()
{
	ABCHECK(CurrentStatData != nullptr, 0.0f);
	return (CurrentStatData->MaxHP < KINDA_SMALL_NUMBER) ? 0.0f : (CurrentHP / CurrentStatData->MaxHP);
}



// Called every frame
//void UPCharacterStatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
//{
//	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
//
//	// ...
//}

