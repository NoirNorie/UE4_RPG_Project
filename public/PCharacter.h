// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "CoreMinimal.h"
#include "Upgrade.h"
// 캐릭터 상위 헤더
#include "GameFramework/Character.h"
// 카메라 헤더
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
// 캐릭터 이동 컴포넌트 헤더
#include "GameFramework/CharacterMovementComponent.h"

#include "PCharacter.generated.h"

UCLASS()
class UPGRADE_API APCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	enum class EControlMode
	{
		GTA,
		DIABLO
	};


	void SetControlMode(EControlMode NewControlMode);
	//EControlMode CurrentControlMode = EControlMode::GTA;
	//FVector DirectionToMove = FVector::ZeroVector;
	EControlMode CurrentControlMode;
	FVector DirectionToMove;

	float ArmLengthTo = 0.0f;
	FRotator ArmRotationTo = FRotator::ZeroRotator;
	float ArmLengthSpeed = 0.0f;
	float ArmRotationSpeed = 0.0f;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// 플레이어 조작을 바인딩할 함수(엔진 함수)
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// 카메라
	UPROPERTY(VisibleAnywhere, category = Camera)
	USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere, Category = Camera)
	UCameraComponent* Camera;

private:
	// 카메라 상하좌우 조작
	void UpDown(float NewAxisValue);
	void LeftRight(float NexAxisValue);
	void LookUp(float NewAxisValue);
	void Turn(float NewAxisValue);

	void ViewChange();

};
