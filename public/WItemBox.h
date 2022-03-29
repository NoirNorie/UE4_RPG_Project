// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "CoreMinimal.h"
#include "Upgrade.h"
#include "GameFramework/Actor.h"
#include "WItemBox.generated.h"

UCLASS()
class UPGRADE_API AWItemBox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWItemBox();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

public:	
	//// Called every frame
	// virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, Category = Box)
		UBoxComponent* Trigger;
	UPROPERTY(VisibleAnywhere, Category = Box)
		UStaticMeshComponent* Box;
	
	UPROPERTY(VisibleAnywhere, Category = Effect)
		UParticleSystemComponent* Effect;
	// 이펙트 표현에 사용할 컴포넌트

	UPROPERTY(EditInstanceOnly, Category = Box)
		TSubclassOf<class AWWeapon> WeaponItemClass;
	/*
		TSubclassOf 키워드
		- 상속받은 클래스들로 목록을 한정하도록 해주는 키워드
		- 목록에서 아이템 상자와 이를 선언한 클래스 목록만이 보인다.
	*/


private:
	UFUNCTION()
		void OnCharacterOverlap(UPrimitiveComponent* OverrlappedComp, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	// OnComponentBeginOverlap 델리게이트는 멀티캐스트 델리게이트로 구현되어 있다.
	// 유형과 인자를 모두 복사해 매크로 설정과 동일한 멤버 함수를 선언한다
	// 이를 해당 델리게이트에 바인딩 할 시 Overlap 발생 시마다 바인딩 멤버 함수가 호출된다.

	UFUNCTION()
		void OnEffectFinished(class UParticleSystemComponent* PSystem);
	/*
		다이나믹 델리게이트 형식 = UFUCTION() 매크로로 리플렉션에 등록해야 쓸 수 있다.
		- C++ 자체적으로는 델리게이트와 리플렉션이 없다
		
	*/

};
