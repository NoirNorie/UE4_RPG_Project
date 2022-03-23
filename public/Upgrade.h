// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once


#include "EngineMinimal.h"
// #include "CoreMinimal.h"
/*
	엔진 미니멀이 더 큰 범주의 헤더
	- EngineMinimal.h > CoreUObject.h > Core.h > CoreMinimal.h

*/

DECLARE_LOG_CATEGORY_EXTERN(Upgrade, Log, All);

#define ABLOG_CALLINFO (FString(__FUNCTION__) + TEXT("(") + FString::FromInt(__LINE__) + TEXT(")"))

// 코드가 존재하는 파일 이름과 함수, 그리고 라인 정보를 추가해 게임이름 카테고리로 로그를 남긴다.
// 로그를 사용한 함수의 실행 시점을 파악할 때 사용한다
#define ABLOG_S(Verbosity) UE_LOG(Upgrade, Verbosity, TEXT("%s"), *ABLOG_CALLINFO)


#define ABLOG(Verbosity, Format, ...) UE_LOG(Upgrade, Verbosity, TEXT("%s%s"), *ABLOG_CALLINFO, *FString::Printf(Format, ##__VA_ARGS__))