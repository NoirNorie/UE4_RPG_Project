// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "CoreMinimal.h"
#include "Upgrade.h"
#include "Engine/GameInstance.h"
#include "Engine/DataTable.h"
#include "Engine/StreamableManager.h"
#include "PGameInstance.generated.h"

USTRUCT(BlueprintType)
struct FPCharacterData : public FTableRowBase // FTableRowBase 구조체를 상속받는 구조체
{
	GENERATED_BODY()
public:
	FPCharacterData() : Level(1), MaxHP(100.0f), Attack(10.0f), DropExp(10), NextExp(30) {} // 초기화 리스트 방식의 초기화 방법(생성 전 초기화)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
		int32 Level;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
		float MaxHP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
		float Attack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
		int32 DropExp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
		int32 NextExp;
};
/*
	게임 인스턴스에서 FPCharacterData 구조체를 컴파일하고 CSV데이터를 임포트한다.
	- 
*/



// 이 게임인스턴스가 게임을 관리하기 위해 프로젝트세팅->맵&모드의 GameInstance를 이 게임 인스턴스로 변경한다.

/**
 * 
 */
UCLASS()
class UPGRADE_API UPGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	UPGameInstance();
	
	virtual void Init() override;

	FPCharacterData* GetPCharacterData(int32 Level);

	FStreamableManager StreamableManager;
	/*
		게임 진행 중에도 비동기 방식으로 애셋을 로딩할 수 있게 하는 클래스
		- 프로젝트에서는 1개만 존재하도록 하는 것이 권장된다.
		- 그래 게임 내에 하나만 존재하는 게임 인스턴스 클래스에서 사용
	*/

private:
	UPROPERTY()
		class UDataTable* PCharacterTable;
	
};
