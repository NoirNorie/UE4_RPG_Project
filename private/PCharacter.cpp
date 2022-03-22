// Fill out your copyright notice in the Description page of Project Settings.


#include "PCharacter.h"

// Sets default values
APCharacter::APCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// 카메라 연결
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	SpringArm->SetupAttachment(RootComponent);
	Camera->SetupAttachment(SpringArm);

	SpringArm->TargetArmLength = 400.0f; // 스프링 암의 길이는 400

	// 캐릭터의 스켈레탈 메시를 가져옴
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>SK_Character(TEXT(""));
	if (SK_Character.Succeeded()) GetMesh()->SetSkeletalMesh(SK_Character.Object);
	
	// 사용할 애니메이션의 모드를 지정한다
	// 블루프린트로 만든 것을 쓸 거라고 하는 것
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	
	// 캐릭터에 사용할 애니메이션을 가져오고 지정함
	static ConstructorHelpers::FClassFinder<UAnimInstance>Character_Anim(TEXT(""));
	if (Character_Anim.Succeeded()) GetMesh()->SetAnimInstanceClass(Character_Anim.Class);

	SetControlMode(0);
}

// Called when the game starts or when spawned
void APCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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

}

void APCharacter::SetControlMode(int32 ControlMode)
{
	if (ControlMode == 0)
	{
		SpringArm->TargetArmLength = 450.0f;
		SpringArm->SetRelativeRotation(FRotator::ZeroRotator);
		SpringArm->bUsePawnControlRotation = true;
		SpringArm->bInheritPitch = true;
		SpringArm->bInheritRoll = true;
		SpringArm->bInheritYaw = true;
		SpringArm->bDoCollisionTest = true;
		bUseControllerRotationYaw = false;

		GetCharacterMovement()->bOrientRotationToMovement = true;
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);
	}
}

// 조작 함수

// 카메라 조작
void APCharacter::UpDown(float NewAxisValue)
{
	//AddMovementInput(GetActorForwardVector(), NewAxisValue);
	AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::X), NewAxisValue);
}
void APCharacter::LeftRight(float NewAxisValue)
{
	// AddMovementInput(GetActorRightVector(), NewAxisValue);
	AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::Y), NewAxisValue);
}
void APCharacter::LookUp(float NewAxisValue)
{
	AddControllerPitchInput(NewAxisValue);
}
void APCharacter::Turn(float NewAxisValue)
{
	AddControllerPitchInput(NewAxisValue);
}