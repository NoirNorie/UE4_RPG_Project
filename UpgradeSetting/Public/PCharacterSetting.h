// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PCharacterSetting.generated.h"

/**
 * 
 */
UCLASS(config=Upgrade) // ini 파일에서 기본 값을 읽어오기 위해서 config를 사용해야 함
class UPGRADESETTING_API UPCharacterSetting : public UObject
{
	GENERATED_BODY()
public:
	UPCharacterSetting();
	UPROPERTY(config) // 역시 ini 파일에서 기본 값을 읽어오기 위해서 UPROPERTY() 지정자에서도 config를 사용해야 한다.
		TArray<FSoftObjectPath> CharacterAssets;
	/*
		Config 폴더에 위치한 DefaultUpgrad.ini 파일을 읽어 CharacterAssets 값을 설정함
	*/
};

/*
	앞으로 사용할 캐릭터 애셋의 목록을 보관하는 클래스
	- 생성자 코드에 애셋을 코드로 보관하는 것도 가능함
	- 이럴 경우 애셋 변경 시 코드를 다시 만들고 컴파일 해야 함
	- 언리얼 엔진에서는 외부 ini 파일에서 기본 속성 값을 지정하는 기능의 제공됨
*/
/*
	언리얼 엔진이 초기화되면서 엔진 구동에 필요한 모듈들이 순차적으로 로딩된다
	- 모듈이 로딩되며 모듈은 자신에게 속한 모든 언리얼 오브젝트의 기본 값을 지정해 생성
	- 이렇게 생성되는 오브젝트의 기본 값을 클래스 기본 객체(CDO; Class Default Object)라고 함
	- 엔진이 초기화되면 모든 언리얼 오브젝트 CDO가 메모리에 적재된 상태가 된다

	이렇게 적제된 CDO는 GetDefault 함수를 사용해서 가져올 수 있음
	- CDO는 엔진이 종료될 때까지 상주하여 언제든 사용 가능함
*/