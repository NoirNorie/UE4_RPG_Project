// Fill out your copyright notice in the Description page of Project Settings.


#include "WItemBox.h"
#include "WWeapon.h"
#include "PCharacter.h"

// Sets default values
AWItemBox::AWItemBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TRIGGER"));
	Box = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BOX"));

	RootComponent = Trigger;
	Box->SetupAttachment(RootComponent);

	Trigger->SetBoxExtent(FVector(40.0f, 42.0f, 30.0f)); // 박스 콜리전의 Extent = 전체 박스 영역 크기의 절반 값
	static ConstructorHelpers::FObjectFinder<UStaticMesh>BOX_SM(
		TEXT("StaticMesh'/Game/InfinityBladeGrassLands/Environments/Breakables/StaticMesh/Box/SM_Env_Breakables_Box1.SM_Env_Breakables_Box1'")
	);
	if (BOX_SM.Succeeded()) Box->SetStaticMesh(BOX_SM.Object);
	Box->SetRelativeLocation(FVector(0.0f, -3.5f, -30.0f));
	// 콜리전 옵션에서 ItemBox 오브젝트 채널, 프리셋을 생성하고 온다.

	Trigger->SetCollisionProfileName(TEXT("ItemBox"));
	Box->SetCollisionProfileName(TEXT("NoCollision"));

	WeaponItemClass = AWWeapon::StaticClass(); // 무기에 대한 기본 클래스값 지정

}

// Called when the game starts or when spawned
void AWItemBox::BeginPlay()
{
	Super::BeginPlay();
	
}

void AWItemBox::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AWItemBox::OnCharacterOverlap);
}

void AWItemBox::OnCharacterOverlap(UPrimitiveComponent* OverrlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ABLOG_S(Warning);
	auto Chara = Cast<APCharacter>(OtherActor);
	// ABCHECK(nullptr != PlayerCharacter);
	if (nullptr != Chara)
	{
		if (WeaponItemClass != nullptr)
		{
			if (Chara->CanSetWeapon()) // 플레이어가 무기를 장착할 수 있어야 아이템을 장착할 수 있게 한다.
			{
				auto NewWeapon = GetWorld()->SpawnActor<AWWeapon>(WeaponItemClass, FVector::ZeroVector, FRotator::ZeroRotator);
				Chara->SetWeapon(NewWeapon);
			}
			else
			{
				ABLOG(Warning, TEXT("%s can't equip weapon currently"), *Chara->GetName());
			}
		}
		//else
		//{
		//	ABLOG(Warning, TEXT("%s can't equip weapon currently"), "Null");
		//}

	}
}



//// Called every frame
//void AWItemBox::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}