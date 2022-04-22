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

DECLARE_MULTICAST_DELEGATE(FOnAttackEndDelegate);
//AI에게 공격명령을 내리고 공격이 종료되면 공격 태스크에서 알림을 받을 수 있도록 하는 델리게이트
DECLARE_MULTICAST_DELEGATE(FOnDamagedEndDelegate);

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

	// 조작 방법을 기록할 열거형
	enum class EControlMode
	{
		GTA,
		DIABLO,
		NPC
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
	virtual void PostInitializeComponents() override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
		class AController* EventInstigator, AActor* DamageCauser) override;
	// 컨트롤러가 누구인지 알아낼 함수
	virtual void PossessedBy(AController* NewController) override;


	// 카메라
	UPROPERTY(VisibleAnywhere, category = Camera)
	USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere, Category = Camera)
	UCameraComponent* Camera;

	// 공격 판정용 변수들
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		float AttackRange;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAcceses = true))
		float AttackRadius;

	// 무기 관련 변수들
	UPROPERTY(VisibleAnywhere, Category = Weapon)
		USkeletalMeshComponent* Weapon;

	bool CanSetWeapon();
	void SetWeapon(class AWWeapon* NewWeapon); // 무기가 없으면 무기를 장착하고 무기의 액터를 소유자로 변환하는 함수

	UPROPERTY(VisibleAnywhere, Category = Weapon)
		class AWWeapon* CurrentWeapon;

	// 스텟을 읽어올 컴포넌트
	UPROPERTY(VisibleAnywhere, Category = Stat)
		class UPCharacterStatComponent* CharacterStat;

	// 체력바를 표시할 컴포넌트
	UPROPERTY(VisibleAnywhere, Category = UI)
		class UWidgetComponent* HPBarWidget;

	UPROPERTY(VisibleAnywhere, Category = CharacterClass)
		int32 CharaClass;

	// 공격 함수
	void Attack();
	FOnAttackEndDelegate OnAttackEnd;

	//// 피격 함수
	//void BeingDamaged();
	//FOnDamagedEndDelegate OnDamagedEnd;
	

	// 캐릭터 상태를 가져오거나 설정하는 함수
	void SetCharacterState(ECharacterState NewState);
	ECharacterState GetCharacterState() const;

	// 경험치
	int32 GetExp() const;

	int32 GetCharaClass();

private:
	// 카메라 상하좌우 조작
	void UpDown(float NewAxisValue);
	void LeftRight(float NexAxisValue);
	void LookUp(float NewAxisValue);
	void Turn(float NewAxisValue);
	
	// 액션 바인드
	void ViewChange();
	// void Jump(); // 점프 함수는 캐릭터 클래스에 이미 존재한다.

	// 비동기 로딩을 수행할 함수
	void OnAssetLoadCompleted();
	bool bLoadComp;

	UPROPERTY()
		class UPAnimInstance* PlayerAnim;

	// 공격 모션 처리
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		bool IsAttacking;
	UFUNCTION()
		void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	//// 데미지를 받은 경우 처리
	//UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	//	bool IsDamaged;
	//UFUNCTION()
	//	void OnDamagedMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	void AttackStartComboState();
	void AttackEndComboState();
	void AttackCheck();


	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		bool CanNextCombo;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		bool IsComboInputOn;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		int32 CurrentCombo;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		int32 MaxCombo;

	FSoftObjectPath CharacterAssetToLoad = FSoftObjectPath(nullptr);
	TSharedPtr<struct FStreamableHandle> AssetStreamingHandle;

	int32 AssetIndex = 0;
	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadOnly, Category = State, Meta = (AllowPrivateAccess = true))
		ECharacterState CurrentState;
	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadOnly, Category = State, Meta = (AllowPrivateAccess = true))
		bool bIsPlayer;

	UPROPERTY()
		class ANAIController* AIController;
	UPROPERTY()
		class APPlayerController* PController;
	/*
		현재 상황에서는 멀티가 아닌 싱글 플레이 상태로 구현하였고 캐릭터 클래스를 플레이어와 NPC가 공유중
		- AI인지 플레이어인지를 구분할 수 있어야 한다
		- 이를 구분할 수 있는 확실한 시점 중 하나가 BeginPlay() 함수 내부
		- 플레이어가 캐릭터를 조종하는 경우를 AssetIndex = 4로 임시로 구분함
	*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = State, Meta = (AllowPrivateAccess = true))
		float DeadTimer;
	FTimerHandle DeadTimerHandle = {  };

	TMap<int32, TSubclassOf<UAnimInstance>> ANImap;
};


/*
- 플레이어 콜리전관련
- PlayerCharacter = ECC_GameTraceChannel1
- Attack		  = ECC_GameTraceChannel2
+DefaultChannelResponses=(Channel=ECC_GameTraceChannel1,DefaultResponse=ECR_Block,bTraceType=False,bStaticObject=False,Name="PlayerCharacter")
+DefaultChannelResponses=(Channel=ECC_GameTraceChannel2,DefaultResponse=ECR_Ignore,bTraceType=True,bStaticObject=False,Name="Attack")

*/