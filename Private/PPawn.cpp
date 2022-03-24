// Fill out your copyright notice in the Description page of Project Settings.


#include "PPawn.h"

// Sets default values
APPawn::APPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Movement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement"));
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	RootComponent = Capsule;
	Mesh->SetupAttachment(Capsule);
	SpringArm->SetupAttachment(Capsule);
	Camera->SetupAttachment(SpringArm);

	Capsule->SetCapsuleHalfHeight(88.0f);
	Capsule->SetCapsuleRadius(34.0f);
	Mesh->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));

	SpringArm->TargetArmLength = 400.0f;
	SpringArm->SetRelativeRotation(FRotator(-15.0f, 0.0f, 0.0f));

	// 스켈레탈 메시와 연결
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>SK_Character(TEXT("SkeletalMesh'/Game/Import/GKnight/Meshes/SK_GothicKnight_VA.SK_GothicKnight_VA'"));
	if (SK_Character.Succeeded()) Mesh->SetSkeletalMesh(SK_Character.Object);

	// 스켈레탈 메시의 애니메이션 모드 연결
	Mesh->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	static ConstructorHelpers::FClassFinder<UAnimInstance>Character_Anim(
		TEXT("/Game/PlayerCharacter/Animations/PlayerAnimation.PlayerAnimation_C"));
	if (Character_Anim.Succeeded()) Mesh->SetAnimInstanceClass(Character_Anim.Class);


}

// Called when the game starts or when spawned
void APPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APPawn::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	ABLOG_S(Warning);
}

void APPawn::PossessedBy(AController* NewController)
{
	ABLOG_S(Warning);
	Super::PossessedBy(NewController);
}

// Called to bind functionality to input
void APPawn::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("UpDown"), this, &APPawn::UpDown);
	PlayerInputComponent->BindAxis(TEXT("LeftRight"), this, &APPawn::LeftRight);

}

/*
	폰을 조종하기 위한 입력 로직은 폰 클래스에서 구현하는 것이 일반적
	- 컨트롤러 클래스에 입력을 처리하는 코드가 구현되면 컨트롤러에서 입력이 처리되어 폰에 전달되지 않음
	- 컨트롤러 클래스에서 처리되는 것
*/
void APPawn::UpDown(float NewAxisValue)
{
	ABLOG(Warning, TEXT("%f"), NewAxisValue);
	AddMovementInput(GetActorForwardVector(), NewAxisValue);
	// AddMovementInput: 월드 좌표계를 기준으로 하는 방향 벡터 데이터를 전달해야 한다
	// 월드 좌표계를 기준으로액터의 전진 방향의 벡터 데이터는 GetActorForwardVector 함수를 이용해서 가져올 수 있다.
	// - 이 값을 WorldDirection 인자에 넘겨준다.
}
void APPawn::LeftRight(float NewAxisValue)
{
	ABLOG(Warning, TEXT("%f"), NewAxisValue);
	AddMovementInput(GetActorRightVector(), NewAxisValue);
}
