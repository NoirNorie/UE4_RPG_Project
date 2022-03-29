// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "CoreMinimal.h"
#include "Upgrade.h"
#include "Components/ActorComponent.h"
#include "PCharacterStatComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UPGRADE_API UPCharacterStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPCharacterStatComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void InitializeComponent() override;

public:	
	void SetNewLevel(int32 NewLevel);


private:

	struct FPCharacterData* CurrentStatData = nullptr;
	// 캐릭터 스텟 구조체

	UPROPERTY(EditInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
		int32 Level;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat, Meta = (AllowPrivateAcess = true))
		float CurrentHP;
	/*
		Transient: 휘발성
		- 언리얼 오브젝트에서는 직렬화(Serialization) 기능이 존재한다
		- 오브젝트의 UPROPERTY 속성을 저장하고 로딩하는 것이 가능한 것
		- CurrentHP 값은 게임을 시작할 때마다 변경되어 이 값을 보관할 필요가 딱히 없음(오히려 오브젝트 저장시 자원만 소모함)
		- 직렬화에서 제외시키는 키워드라고 생각하면 된다.
	*/










	// Called every frame
	// virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	// 역시 틱 함수는 안쓴다.	
};