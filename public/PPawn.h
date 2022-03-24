// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "CoreMinimal.h"
#include "Upgrade.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "PPawn.generated.h"

UCLASS()
class UPGRADE_API APPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void PostInitializeComponents() override;
	virtual void PossessedBy(AController* NewController) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// 캐릭터 표현에 사용할 요소들
	UPROPERTY(VisibleAnywhere, Category = Collision)
		UCapsuleComponent* Capsule;
	UPROPERTY(VisibleAnywhere, Category = Visual)
		USkeletalMeshComponent* Mesh;
	UPROPERTY(VisibleAnywhere, Category = Movement)
		UFloatingPawnMovement* Movement;
	UPROPERTY(VisibleAnywhere, Category = Camera)
		USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere, CAtegory = Camera)
		UCameraComponent* Camera;

private:
	// 카메라 상하좌우 조작
	void UpDown(float NewAxisValue);
	void LeftRight(float NexAxisValue);
	void LookUp(float NewAxisValue);
	void Turn(float NewAxisValue);


};
