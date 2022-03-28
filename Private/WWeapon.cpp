// Fill out your copyright notice in the Description page of Project Settings.


#include "WWeapon.h"

// Sets default values
AWWeapon::AWWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false; // 이것까지 변경해줘야 틱 함수가 잠긴다.

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WEAPON"));
	RootComponent = Weapon; // 루트를 이 변수로 설정한다.
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>Weapon_SK(
		TEXT("SkeletalMesh'/Game/InfinityBladeWeapons/Weapons/Blade/Swords/Blade_BlackKnight/SK_Blade_BlackKnight.SK_Blade_BlackKnight'")
	);

	if (Weapon_SK.Succeeded()) Weapon->SetSkeletalMesh(Weapon_SK.Object);
	Weapon->SetCollisionProfileName(TEXT("NoCollision"));

}

// Called when the game starts or when spawned
void AWWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}





//// Called every frame
//void AWWeapon::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}