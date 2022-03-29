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
		CurrentHP = CurrentStatData->MaxHP;
	}
	else
	{
		ABLOG(Error, TEXT("Level (%d) data Doesn't exist"), NewLevel);
	}

}


// Called every frame
//void UPCharacterStatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
//{
//	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
//
//	// ...
//}

