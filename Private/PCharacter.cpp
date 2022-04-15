// Fill out your copyright notice in the Description page of Project Settings.


#include "PCharacter.h"
#include "PAnimInstance.h"
#include "WWeapon.h"
#include "PCharacterStatComponent.h"
#include "DrawDebugHelpers.h"
#include "Components/WidgetComponent.h"
#include "PCharacterWidget.h"
#include "NAIController.h"
#include "PCharacterSetting.h"
#include "PGameInstance.h"
#include "PPlayerController.h"
#include "PPlayerState.h"
#include "PHudWidget.h"
#include "SGameMode.h"

// Sets default values
APCharacter::APCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 카메라 연결
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	SpringArm->SetupAttachment(GetCapsuleComponent());
	Camera->SetupAttachment(SpringArm);

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));
	SpringArm->TargetArmLength = 800.0f; // 스프링 암의 길이는 800
	SpringArm->SetRelativeRotation(FRotator(-15.0f, 0.0f, 0.0f));

	CharaClass = 1;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>SK_Character(TEXT("SkeletalMesh'/Game/PlayerCharacter/Knight/Knight.Knight'"));
	if (SK_Character.Succeeded()) GetMesh()->SetSkeletalMesh(SK_Character.Object);
	static ConstructorHelpers::FClassFinder<UAnimInstance>Character_Anim(TEXT("/Game/PlayerCharacter/Knight/KnightAnimation.KnightAnimation_C"));
	if (Character_Anim.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(Character_Anim.Class);
	}

	//static ConstructorHelpers::FClassFinder<UAnimInstance>AnimLoad1(TEXT("/Game/PlayerCharacter/Hammer/HammerAnimation.HammerAnimation_C"));
	//if (AnimLoad1.Succeeded())
	//{
	//	ANImap.Add(0, AnimLoad1.Class);
	//}
	//static ConstructorHelpers::FClassFinder<UAnimInstance>AnimLoad2(TEXT("/Game/PlayerCharacter/2Hand/Hand2Animation.Hand2Animation_C"));
	//if (AnimLoad2.Succeeded())
	//{
	//	ANImap.Add(1, AnimLoad2.Class);
	//}

	// 사용할 애니메이션의 모드를 지정한다
	// 블루프린트로 만든 것을 쓸 거라고 하는 것
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);


	SetControlMode(EControlMode::DIABLO);
	// 화면 전환시 조작 속도와 회전 속도
	ArmLengthSpeed = 3.0f;
	ArmRotationSpeed = 10.0f;
	GetCharacterMovement()->JumpZVelocity = 800.0f;


	// 공격용 함수
	IsAttacking = false;
	MaxCombo = 3; // 기본적으로 세번 때림
	AttackEndComboState();

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("PlayerCharacter"));

	AttackRange = 200.0f;
	AttackRadius = 50.0f;

	//// 무기 장착용 변수 초기화
	//FName WeaponSocket(TEXT("Hand_R_Socket"));
	//if (GetMesh()->DoesSocketExist(WeaponSocket)) // 소켓이 존재하는지 검사한다
	//{
	//	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon"));
	//	static ConstructorHelpers::FObjectFinder<USkeletalMesh>Weapon_SK(
	//		TEXT("SkeletalMesh'/Game/InfinityBladeWeapons/Weapons/Blade/Swords/Blade_BlackKnight/SK_Blade_BlackKnight.SK_Blade_BlackKnight'")
	//	);
	//	if (Weapon_SK.Succeeded()) Weapon->SetSkeletalMesh(Weapon_SK.Object);
	//	Weapon->SetupAttachment(GetMesh(), WeaponSocket);
	//}

	CurrentWeapon = nullptr;

	// 캐릭터 스텟
	CharacterStat = CreateDefaultSubobject<UPCharacterStatComponent>(TEXT("CharacterStat"));
	
	// 캐릭터 체력바 위젯
	/*
		캐릭터의 위젯과 스텟 컴포넌트의 상호작용을 위해 델리게이트를 사용함
		- 상호 의존성을 가지지 않게 만들기 위해서 델리게이트를 사용하는 것
	*/


	HPBarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBarWidget"));
	HPBarWidget->SetupAttachment(GetMesh());

	HPBarWidget->SetRelativeLocation(FVector(0.0f, 0.0f, 180.0f));
	HPBarWidget->SetWidgetSpace(EWidgetSpace::Screen);

	static ConstructorHelpers::FClassFinder<UUserWidget>UI_HUD(TEXT("/Game/BPS/Widgets/UI_HPBar.UI_HPBar_C"));
	if (UI_HUD.Succeeded())
	{
		HPBarWidget->SetWidgetClass(UI_HUD.Class);
		HPBarWidget->SetDrawSize(FVector2D(150.0f, 50.0f));
	}
	AIControllerClass = ANAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	// EAutoPossessAI::PlacedInWorldOrSpawned: 이 클래스를 사용하는 캐릭터 중 플레이어가 컨트롤 하는 것을 제외한다면 스스로 움직이게 된다.

	//// 로그 출력 테스트
	//auto DefaultSetting = GetDefault<UPCharacterSetting>();
	//if (DefaultSetting->CharacterAssets.Num() > 0)
	//{
	//	for (auto CharacterAsset : DefaultSetting->CharacterAssets)
	//	{
	//		ABLOG(Warning, TEXT("Character Asset : %s"), *CharacterAsset.ToString());
	//	}
	//}

	// AssetIndex = 2;
	SetActorHiddenInGame(true);
	HPBarWidget->SetHiddenInGame(true);
	// bCanBeDamaged = false; // 책이 나올 당시에는 이렇게 접근이 가능했음
	SetCanBeDamaged(false); // 현재는 이렇게 Setter 함수 개념으로 접근해야 함

	DeadTimer = 5.0f;

}

// Called when the game starts or when spawned
void APCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	// 액터를 부착하는 경우 여기에서 해야 한다
	// 생성자에서 할 경우 크래시 리포트가 나온다.
	//FName WeaponSocket(TEXT("Hand_R_Socket"));
	//auto CurWeapon = GetWorld()->SpawnActor<AWWeapon>(FVector::ZeroVector, FRotator::ZeroRotator);
	//if (nullptr != CurWeapon)
	//{
	//	CurWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, WeaponSocket);
	//}

	auto CharacterWidget = Cast<UPCharacterWidget>(HPBarWidget->GetUserWidgetObject());
	if (CharacterWidget != nullptr)	CharacterWidget->BindCharacterStat(CharacterStat);

	bIsPlayer = IsPlayerControlled();
	if (bIsPlayer) // 플레이어가 컨트롤하고 있는 캐릭터의 경우
	{
		PController = Cast<APPlayerController>(GetController()); // 플레이어 컨트롤러
		ABCHECK(PController != nullptr);
	}
	else // AI가 컨트롤하고 있는 경우
	{
		AIController = Cast<ANAIController>(GetController()); // AI 컨트롤러
		ABCHECK(AIController != nullptr);
	}

	auto DefaultSetting = GetDefault<UPCharacterSetting>(); // 캐릭터 세팅 클래스에서 애셋을 가져온다
	if (bIsPlayer)
	{
		AssetIndex = 2;
	}
	else
	{
		AssetIndex = FMath::RandRange(0, DefaultSetting->CharacterAssets.Num() - 1);
	}

	// 캐릭터의 스켈레탈 메시 애셋과 애니메이션을 가져옴
	CharacterAssetToLoad = DefaultSetting->CharacterAssets[AssetIndex];

	auto PGameInst = Cast<UPGameInstance>(GetGameInstance());
	AssetStreamingHandle = PGameInst->StreamableManager.RequestAsyncLoad(CharacterAssetToLoad,
		FStreamableDelegate::CreateUObject(this, &APCharacter::OnAssetLoadCompleted)); // 캐릭터 애셋을 가져옴
	SetCharacterState(ECharacterState::LOADING);
	PlayerAnim->SetMontageAnim(AssetIndex);

}

void APCharacter::SetCharacterState(ECharacterState NewState)
{
	ABCHECK(CurrentState != NewState);
	CurrentState = NewState;

	switch (CurrentState)
	{
	case ECharacterState::LOADING:
	{

		if (bIsPlayer)
		{
			DisableInput(PController);

			PController->GetHudWidget()->BindCharacterStat(CharacterStat);

			auto PState = Cast<APPlayerState>(GetPlayerState());
			ABCHECK(PState != nullptr);
			CharacterStat->SetNewLevel(PState->GetCharacterLevel());
		}
		else // 플레이어가 아닐 경우 스테이지 수에 비례하여 더 강력해진다.
		{
			auto PGM = Cast<ASGameMode>(GetWorld()->GetAuthGameMode());
			ABCHECK(PGM != nullptr);
			int32 TargetLevel = FMath::CeilToInt(((float)PGM->GetStage() * 0.8f));
			int32 FinalLevel = FMath::Clamp<int32>(TargetLevel, 1, 20);
			ABLOG(Warning, TEXT("New NPC LEVEL : %d"), FinalLevel);
			CharacterStat->SetNewLevel(FinalLevel);
		}
		SetActorHiddenInGame(true);
		HPBarWidget->SetHiddenInGame(true);
		SetCanBeDamaged(false);
		break;
	}
	case ECharacterState::READY:
	{
		SetActorHiddenInGame(false);
		HPBarWidget->SetHiddenInGame(false);
		SetCanBeDamaged(true);
		CharacterStat->OnHPIsZero.AddLambda([this]()->void {
			SetCharacterState(ECharacterState::DEAD);
			}); // 캐릭터의 체력이 0이 된다면 DEAD 스테이트로 변경하는 람다식

		auto CharaWidget = Cast<UPCharacterWidget>(HPBarWidget->GetUserWidgetObject());
		ABCHECK(CharaWidget != nullptr);
		CharaWidget->BindCharacterStat(CharacterStat);

		// 플레이어, AI에 따라서 다음이 정해진다.
		if (bIsPlayer)
		{
			SetControlMode(EControlMode::DIABLO);
			GetCharacterMovement()->MaxWalkSpeed = 800.0f;
			EnableInput(PController);

		}
		else
		{
			SetControlMode(EControlMode::NPC);
			GetCharacterMovement()->MaxWalkSpeed = 400.0f;
			AIController->RunAI(); // 비헤이비어 트리를 동작시킨다.

		}
		break;
	}
	case ECharacterState::DEAD:
	{
		SetActorEnableCollision(false);
		GetMesh()->SetHiddenInGame(false);
		HPBarWidget->SetHiddenInGame(true);
		PlayerAnim->SetDeadAnim();
		SetCanBeDamaged(false);

		if (bIsPlayer)
		{
			DisableInput(PController);
		}
		else
		{
			AIController->StopAI();
		}

		GetWorld()->GetTimerManager().SetTimer(DeadTimerHandle, FTimerDelegate::CreateLambda(
			[this]()->void {
				if (bIsPlayer) PController->RestartLevel();
				else Destroy();
			}), DeadTimer, false);

		break;
	}
	}
}
ECharacterState APCharacter::GetCharacterState() const
{
	return CurrentState;
}


void APCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	//auto AnimInstance = Cast<UPAnimInstance>(GetMesh()->GetAnimInstance());

	PlayerAnim = Cast<UPAnimInstance>(GetMesh()->GetAnimInstance());
	ABCHECK(nullptr != PlayerAnim);

	PlayerAnim->OnMontageEnded.AddDynamic(this, &APCharacter::OnAttackMontageEnded);
	UE_LOG(LogTemp, Log, TEXT("Montage Check %d"), 0);

	PlayerAnim->OnNextAttackCheck.AddLambda([this]()->void {
		ABLOG(Warning, TEXT("OnNextAttackCheck"));
		CanNextCombo = false;
		if (IsComboInputOn)
		{
			AttackStartComboState();
			PlayerAnim->JumpToAttackMontageSection(CurrentCombo);
		}
	});
	UE_LOG(LogTemp, Log, TEXT("Montage Check %d"), 1);
	PlayerAnim->OnAttackHitCheck.AddUObject(this, &APCharacter::AttackCheck);
	// 공격 판정을 위해 애니메이션에 전달해준다.


	//CharacterStat->OnHPIsZero.AddLambda([this]()->void {
	//	ABLOG(Warning, TEXT("OnHPIsZero"));
	//	PlayerAnim->SetDeadAnim();
	//	SetActorEnableCollision(false);
	//}); // 데미지 처리 중 체력이 0 이하로 떨어지면 람다식으로 액터의 콜리전을 제거해준다.
	// 캐릭터 스테이트에서 동일한 람다식을 정의하였음
	// 더 이상 필요 없는 구문

	//// 4.21버전 이후로 이 구분이 BeginPlay() 함수로 이동해야 정상적으로 동작함
	//auto CharacterWidget = Cast<UPCharacterWidget>(HPBarWidget->GetUserWidgetObject());
	//if (CharacterWidget != nullptr) CharacterWidget->BindCharacterStat(CharacterStat);


}

// Called every frame
void APCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SpringArm->TargetArmLength = FMath::FInterpTo(SpringArm->TargetArmLength, ArmLengthTo, DeltaTime, ArmLengthSpeed);

	switch (CurrentControlMode)
	{
	case EControlMode::DIABLO:
		//SpringArm->RelativeRotation = FMath::RInterpTo(SpringArm->RelativeRotation, ArmRotationTo, DeltaTime, ArmRotationSpeed);
		// 4.24 버전에서 relativeRotation 접근 권한이 변경되어 아래와 같이 수정해야 한다.
		FRotator TempRotation = FMath::RInterpTo(SpringArm->GetRelativeRotation(), ArmRotationTo, DeltaTime, ArmRotationSpeed);
		SpringArm->SetRelativeRotation(TempRotation);
		break;
	}

	switch (CurrentControlMode)
	{
	case EControlMode::DIABLO:
		
		if (DirectionToMove.SizeSquared() > 0.0f)
		{
			GetController()->SetControlRotation(FRotationMatrix::MakeFromX(DirectionToMove).Rotator());
			AddMovementInput(DirectionToMove);
		}
		break;
	}

}



// Called to bind functionality to input
void APCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	// 마우스 상하 조작
	PlayerInputComponent->BindAxis(TEXT("UpDown"), this, &APCharacter::UpDown);
	PlayerInputComponent->BindAxis(TEXT("LeftRight"), this, &APCharacter::LeftRight);
	// 마우스 좌우 조작
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APCharacter::LookUp);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &APCharacter::Turn);


	PlayerInputComponent->BindAction(TEXT("ViewChange"), EInputEvent::IE_Pressed, this, &APCharacter::ViewChange);
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &APCharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Attack"), EInputEvent::IE_Pressed, this, &APCharacter::Attack);
}

void APCharacter::SetControlMode(EControlMode NewControlMode)
{
	CurrentControlMode = NewControlMode;

	switch (CurrentControlMode)
	{
	case EControlMode::GTA:
		// SpringArm->TargetArmLength = 450.0f;
		// SpringArm->SetRelativeRotation(FRotator::ZeroRotator);
		ArmLengthTo = 800.0f;
		SpringArm->bUsePawnControlRotation = true;
		SpringArm->bInheritPitch = true;
		SpringArm->bInheritRoll = true;
		SpringArm->bInheritYaw = true;
		SpringArm->bDoCollisionTest = true;
		bUseControllerRotationYaw = false;
		GetCharacterMovement()->bOrientRotationToMovement = true;
		GetCharacterMovement()->bUseControllerDesiredRotation = false;
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);
		break;
	case EControlMode::DIABLO:
		// SpringArm->TargetArmLength = 800.0f;
		// SpringArm->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f));
		ArmLengthTo = 800.0f;
		ArmRotationTo = FRotator(-45.0f, 0.0f, 0.0f);
		SpringArm->bUsePawnControlRotation = false;
		SpringArm->bInheritPitch = false;
		SpringArm->bInheritRoll = false;
		SpringArm->bInheritYaw = false;
		SpringArm->bDoCollisionTest = false;
		bUseControllerRotationYaw = false;
		GetCharacterMovement()->bOrientRotationToMovement = false;
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);
		break;
	case EControlMode::NPC:
		bUseControllerRotationYaw = false;
		GetCharacterMovement()->bUseControllerDesiredRotation = false;
		GetCharacterMovement()->bOrientRotationToMovement = true;
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 480.0f, 0.0f);
		break;
	}
}

// 조작 함수

// 축 함수
void APCharacter::UpDown(float NewAxisValue)
{
	//AddMovementInput(GetActorForwardVector(), NewAxisValue);
	// AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::X), NewAxisValue);

	switch (CurrentControlMode)
	{
	case EControlMode::GTA:
		AddMovementInput(FRotationMatrix(FRotator(0.0f, GetControlRotation().Yaw, 
			0.0f)).GetUnitAxis(EAxis::X), NewAxisValue);
		break;
	case EControlMode::DIABLO:
		DirectionToMove.X = NewAxisValue;
		break;
	}


}
void APCharacter::LeftRight(float NewAxisValue)
{
	// AddMovementInput(GetActorRightVector(), NewAxisValue);
	// AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::Y), NewAxisValue);

	switch (CurrentControlMode)
	{
	case EControlMode::GTA:
		AddMovementInput(FRotationMatrix(FRotator(0.0f, GetControlRotation().Yaw,
			0.0f)).GetUnitAxis(EAxis::Y), NewAxisValue);
		break;
	case EControlMode::DIABLO:
		DirectionToMove.Y = NewAxisValue;
		break;
	}

}
void APCharacter::LookUp(float NewAxisValue)
{
	// AddControllerPitchInput(NewAxisValue);
	switch (CurrentControlMode)
	{
	case EControlMode::GTA:
		AddControllerPitchInput(NewAxisValue);
		break;
	}
}
void APCharacter::Turn(float NewAxisValue)
{
	// AddControllerPitchInput(NewAxisValue);
	switch (CurrentControlMode)
	{
	case EControlMode::GTA:
		AddControllerYawInput(NewAxisValue);
		break;
	}
}

// 액션 함수

void APCharacter::ViewChange()
{
	switch (CurrentControlMode)
	{
	case EControlMode::GTA:
		GetController()->SetControlRotation(GetActorRotation());
		SetControlMode(EControlMode::DIABLO);
		break;
	case EControlMode::DIABLO:
		// GetController()->SetControlRotation(SpringArm->RelativeRotation);
		GetController()->SetControlRotation(SpringArm->GetRelativeRotation());
		SetControlMode(EControlMode::GTA);
		break;
	}
}

void APCharacter::Attack()
{
	ABLOG_S(Warning);
	if (IsAttacking)
	{
		ABCHECK(FMath::IsWithinInclusive<int32>(CurrentCombo, 1, MaxCombo));
		if (CanNextCombo)
		{
			IsComboInputOn = true;
		}
	}
	else
	{
		ABCHECK(CurrentCombo == 0);
		AttackStartComboState();

		PlayerAnim->PlayAttackMontage();
		PlayerAnim->JumpToAttackMontageSection(CurrentCombo);
		IsAttacking = true;
	}
}

void APCharacter::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	ABCHECK(IsAttacking);
	ABCHECK(CurrentCombo > 0);
	IsAttacking = false;
	AttackEndComboState();

	OnAttackEnd.Broadcast();
	// 공격이 종료됨을 델리게이트로 알린다
}

void APCharacter::AttackStartComboState()
{
	CanNextCombo = true;
	IsComboInputOn = false;
	ABCHECK(FMath::IsWithinInclusive<int32>(CurrentCombo, 0, MaxCombo - 1));
	CurrentCombo = FMath::Clamp<int32>(CurrentCombo + 1, 1, MaxCombo);
}

void APCharacter::AttackEndComboState()
{
	IsComboInputOn = false;
	CanNextCombo = false;
	CurrentCombo = 0;
}

void APCharacter::AttackCheck()
{
	FHitResult HitResult;
	FCollisionQueryParams Params(NAME_None, false, this);
	bool bResult = GetWorld()->SweepSingleByChannel(
		HitResult,
		GetActorLocation(), GetActorLocation() + GetActorForwardVector() * 200.0f,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2, // 플레이어의 공격이므로 플레이어의 공격 트레이스 채널인 2번 트레이스 채널을 사용함
		FCollisionShape::MakeSphere(50.0f), // 구체 모양의 충돌 도형을 생성하여 충돌을 확인한다.
		Params);


	// 디버그 드로잉
#if ENABLE_DRAW_DEBUG
	FVector TraceVec = GetActorForwardVector() * AttackRange;
	FVector Center = GetActorLocation() + TraceVec * 0.5f;

	float HalfHeight = AttackRange *0.5f + AttackRadius;
	FQuat CapsuleRot = FRotationMatrix::MakeFromZ(TraceVec).ToQuat();
	FColor DrawColor = bResult ? FColor::Green : FColor::Red;
	float DebugLiftTime = 5.0f;

	DrawDebugCapsule(GetWorld(), Center, HalfHeight, AttackRadius, CapsuleRot, DrawColor, false, DebugLiftTime);

#endif

	// 충돌한 개체가 있다면
	if (bResult)
	{
		if (HitResult.Actor.IsValid())
		{
			ABLOG(Warning, TEXT("Hit Actor Name : %s"), *HitResult.Actor->GetName());

			FDamageEvent DamageEvent;
			//HitResult.Actor->TakeDamage(50.0f, DamageEvent, GetController(), this);
			HitResult.Actor->TakeDamage(CharacterStat->GetAttack(), DamageEvent, GetController(), this);
		}
	}

}

// 데미지 함수
float APCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
	class AController* EventInstigator, AActor* DamageCauser)
{
	float FinalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	ABLOG(Warning, TEXT("Actor : %s took Damage : %f"), *GetName(), FinalDamage);

	//if (FinalDamage > 0.0f)
	//{
	//	PlayerAnim->SetDeadAnim();
	//	SetActorEnableCollision(false);
	//}

	CharacterStat->SetDamage(FinalDamage); // 데미지를 전달한다.

	if (CurrentState == ECharacterState::DEAD)
	{
		if (EventInstigator->IsPlayerController())
		{
			auto PCont = Cast<APPlayerController>(EventInstigator);
			ABCHECK(PCont != nullptr, 0.0f);
			PCont->NPCKill(this);
		}
	}

	return FinalDamage;
}

bool APCharacter::CanSetWeapon()
{
	ABLOG_S(Warning);
	return { nullptr == CurrentWeapon };
}
void APCharacter::SetWeapon(AWWeapon* NewWeapon)
{
	ABCHECK(nullptr != NewWeapon && nullptr == CurrentWeapon);
	FName WeaponSocket(TEXT("Hand_R_Socket"));
	if (nullptr != NewWeapon)
	{
		ABLOG_S(Warning);
		NewWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, WeaponSocket);
		NewWeapon->SetOwner(this);
		CurrentWeapon = NewWeapon;
	}
}

void APCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	if (IsPlayerControlled())
	{
		SetControlMode(EControlMode::DIABLO);
		GetCharacterMovement()->MaxWalkSpeed = 600.0f;
	}
	else
	{
		SetControlMode(EControlMode::NPC);
		GetCharacterMovement()->MaxWalkSpeed = 300.0f;
	}


}

void APCharacter::OnAssetLoadCompleted()
{
	USkeletalMesh* AssetLoaded = Cast<USkeletalMesh>(AssetStreamingHandle->GetLoadedAsset());
	AssetStreamingHandle.Reset();
	ABCHECK(AssetLoaded != nullptr);
	UE_LOG(LogTemp, Log, TEXT("ASYNC Load %d"), AssetIndex);
	// 애니메이션도 런타임에 변경해줌
	switch(AssetIndex)
	{
	case 0:
	{
		FString Anim_Path = TEXT("/Game/PlayerCharacter/Ham/HamAnim.HamAnim_C");
		UClass* AssetAnim = StaticLoadClass(UAnimInstance::StaticClass(), NULL, *Anim_Path);
		ABCHECK(AssetAnim != nullptr);
		GetMesh()->SetAnimInstanceClass(AssetAnim);
		UE_LOG(LogTemp, Log, TEXT("Load %d"), 0);
		break;
	}
	case 1:
	{
		FString Anim_Path = TEXT("/Game/PlayerCharacter/Hand2/Hand2Anim.Hand2Anim_C");
		UClass* AssetAnim = StaticLoadClass(UAnimInstance::StaticClass(), NULL, *Anim_Path);
		ABCHECK(AssetAnim != nullptr);
		GetMesh()->SetAnimInstanceClass(AssetAnim);
		UE_LOG(LogTemp, Log, TEXT("Load %d"), 1);
		break;
	}
	case 2:
	{
		FString Anim_Path = TEXT("/Game/PlayerCharacter/Knight/KnightAnimation.KnightAnimation_C");
		UClass* AssetAnim = StaticLoadClass(UAnimInstance::StaticClass(), NULL, *Anim_Path);
		ABCHECK(AssetAnim != nullptr);
		GetMesh()->SetAnimInstanceClass(AssetAnim);
		UE_LOG(LogTemp, Log, TEXT("Load %d"), 2);
		break;
	}
	}

	// GetMesh()->SetAnimInstanceClass(ANImap[AssetIndex]); // 애니메이션도 전환시킴

	GetMesh()->SetSkeletalMesh(AssetLoaded); // 스켈레탈 메시를 가져옴
	//PlayerAnim->SetMontageAnim(AssetIndex);

	//PostInitializeComponents();
	// 애셋을 가져오고 애니메이션을 가져오는 것 까지 성공했다면 준비 상태로 전환시킨다.
	SetCharacterState(ECharacterState::READY);
}

int32 APCharacter::GetExp() const
{
	return CharacterStat->GetDropExp();
}

int32 APCharacter::GetCharaClass()
{
	return AssetIndex;
}