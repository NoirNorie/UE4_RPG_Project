// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once


#include "EngineMinimal.h"
// #include "CoreMinimal.h"
/*
	엔진 미니멀이 더 큰 범주의 헤더
	- EngineMinimal.h > CoreUObject.h > Core.h > CoreMinimal.h

*/

/*
	캐릭터의 스테이트
	- PREINIT: 캐릭터 생성 전의 스테이트
	-> 기본 캐릭터 애셋은 있지만 캐릭터와 UI를 출력하지는 않음
	
	- LOADING: 선택한 캐릭터 애셋을 로딩하는 스테이트
	-> 현재 조종하는 컨트롤러가 플레이어인지 아닌지를 구분할 수 있음
	-> 플레이어인 경우 애셋 로딩이 완료될 때까지 캐릭터를 조종하지 못하도록 입력을 막음
	
	- READY: 캐릭터 애셋 로딩이 완료된 스테이트
	-> 본격적인 플레이가 진행되는 상태로 플레이어가 캐릭터를 조종할 수 있음
	-> AI의 경우 비헤이비어 트리 로직이 구동되어 캐릭터가 동작한다.

	- DEAD: 캐릭터가 사망한 경우의 스테이트
	-> 사망 애니메이션 출력, UI 종료, 충돌 기능 제거, 데미지 처리 중지 등을 수행하는 스테이트
	-> 컨트롤러가 플레이어: 입력 비활성화
	-> 컨트롤러가 AI: 비헤이비어 트리 로직 중단
*/

// 캐릭터의 스테이트를 구분하기 위한 열거형
UENUM(BlueprintType)
enum class ECharacterState :uint8
{
	PREINIT,
	LOADING,
	READY,
	DEAD
};


DECLARE_LOG_CATEGORY_EXTERN(Upgrade, Log, All);

#define ABLOG_CALLINFO (FString(__FUNCTION__) + TEXT("(") + FString::FromInt(__LINE__) + TEXT(")"))

// 코드가 존재하는 파일 이름과 함수, 그리고 라인 정보를 추가해 게임이름 카테고리로 로그를 남긴다.
// 로그를 사용한 함수의 실행 시점을 파악할 때 사용한다
#define ABLOG_S(Verbosity) UE_LOG(Upgrade, Verbosity, TEXT("%s"), *ABLOG_CALLINFO)


#define ABLOG(Verbosity, Format, ...) UE_LOG(Upgrade, Verbosity, TEXT("%s%s"), *ABLOG_CALLINFO, *FString::Printf(Format, ##__VA_ARGS__))

#define ABCHECK(Expr, ...) {if(!(Expr)) {ABLOG(Error, TEXT("ASSERTION : %s"), TEXT("'"#Expr"'")); return __VA_ARGS__;}} 