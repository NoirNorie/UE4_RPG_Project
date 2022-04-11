// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "CoreMinimal.h"
#include "Upgrade.h"
#include "GameFramework/Actor.h"
#include "SSection.generated.h"

/*
	원래는 무한 맵을 만들기 위한 액터를 상속받은 클래스

*/

UCLASS()
class UPGRADE_API ASSection : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASSection();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	// virtual void Tick(float DeltaTime) override;

	// 에디터와 액터를 연동하는 함수
	// 에디터 작업에서 선택한 액터의 속성, 트랜스폼 정보가 변경될 경우 이 함수가 실행된다.
	virtual void OnConstruction(const FTransform& Transform) override;

private:
	/*
		액터의 상태 정의
		- READY: 전투 시작 전
		- BATTLE: 전투 중
		- COMPLETE: 전투 완료
	*/
	enum class ESectionState : uint8
	{
		READY = 0,
		BATTLE,
		COMPLETE
	};
	void setState(ESectionState NewState);
	ESectionState CurrentState = ESectionState::READY;

	UPROPERTY(EditAnywhere, Category = State, Meta = (AllowPrivateAccess = true))
		bool bNoBattle;

	void OnNPCSpawn();

	UFUNCTION()
		void OnKeyNPCDestroyed(AActor* Destroyed);


	UPROPERTY(EditAnywhere, Category = Spawn, Meta = (AllowPrivateAccess = true))
		float EnemySpawnTime;

	FTimerHandle SpawnNPCTimerHandle = {};

};
