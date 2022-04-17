// Fill out your copyright notice in the Description page of Project Settings.


#include "PCharaSelectWidget.h"
#include "PCharacterSetting.h"
#include "PGameInstance.h"
#include "EngineUtils.h"
#include "Animation/SkeletalMeshActor.h"
// 위젯 내용
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "SSaveGame.h"
#include "PPlayerState.h"
#include "PUIPlayerController.h"


void UPCharaSelectWidget::NextCharacter(bool bForward)
{
	bForward ? CurrentIDX++ : CurrentIDX--;

	// 범위 이탈을 잡아내는 구문
	if (CurrentIDX == -1) CurrentIDX = MaxIDX - 1;
	if (CurrentIDX == MaxIDX) CurrentIDX = 0;

	auto CharaSetting = GetDefault<UPCharacterSetting>();
	auto AssetRef = CharaSetting->CharacterAssets[CurrentIDX];

	auto GameInst = GetWorld()->GetGameInstance<UPGameInstance>();
	ABCHECK(GameInst != nullptr);
	ABCHECK(TargetComponent.IsValid());

	USkeletalMesh* Asset = GameInst->StreamableManager.LoadSynchronous<USkeletalMesh>(AssetRef);
	if (Asset != nullptr)
	{
		TargetComponent->SetSkeletalMesh(Asset);
		SetSKANIM();
	}
}

void UPCharaSelectWidget::NativeConstruct()
{
	Super::NativeConstruct();

	CurrentIDX = 0;
	charaName = FText::FromString("Hammer"); // 비동기 로딩 시 가장 첫번째 존재하는 액터는 망치든 캐릭터
	auto CharaSetting = GetDefault<UPCharacterSetting>();
	MaxIDX = CharaSetting->CharacterAssets.Num();


	// 반복자 구문
	// 월드 상에 존재하는 스켈레탈 메시 액터들만을 담고 반복자로 참조할 수 있음
	for (TActorIterator<ASkeletalMeshActor> iter(GetWorld()); iter; ++iter)
	{
		TargetComponent = iter->GetSkeletalMeshComponent();
		break;
	}


	PrevBT = Cast<UButton>(GetWidgetFromName(TEXT("PrevBT")));
	ABCHECK(PrevBT != nullptr);
	PrevBT->OnClicked.AddDynamic(this, &UPCharaSelectWidget::OnPrevClicked);

	NextBT = Cast<UButton>(GetWidgetFromName(TEXT("NextBT")));
	ABCHECK(NextBT != nullptr);
	NextBT->OnClicked.AddDynamic(this, &UPCharaSelectWidget::OnNextClicked);

	StartBT = Cast<UButton>(GetWidgetFromName(TEXT("StartBT")));
	ABCHECK(StartBT != nullptr);
	StartBT->OnClicked.AddDynamic(this, &UPCharaSelectWidget::OnStartClicked);

	CLASSTB = Cast<UTextBlock>(GetWidgetFromName(TEXT("CLASSTB")));
	ABCHECK(CLASSTB != nullptr);
	CLASSTB->SetText(charaName);

}

// 런타임 로딩을 수행하는 함수
void UPCharaSelectWidget::SetSKANIM()
{
	for (TActorIterator<ASkeletalMeshActor> iter(GetWorld()); iter; ++iter)
	{
		TargetComponent = iter->GetSkeletalMeshComponent(); 
		switch (CurrentIDX)
		{
		case 0:
		{
			TargetComponent = iter->GetSkeletalMeshComponent(); // 스켈레탈 메시를 가져온다
			UAnimationAsset* AssetAnim = LoadObject<UAnimationAsset>(NULL,
				TEXT("/Game/PlayerCharacter/Ham/Hammer_Idle.Hammer_Idle"), NULL, LOAD_None, NULL);			// 런타임에 오브젝트를 가져온다
			iter->GetSkeletalMeshComponent()->SetAnimation(AssetAnim);
			iter->GetSkeletalMeshComponent()->PlayAnimation(AssetAnim, true);
			charaName = FText::FromString("Hammer");
			break;
		}
		case 1:
		{
			TargetComponent = iter->GetSkeletalMeshComponent();
			UAnimationAsset* AssetAnim = LoadObject<UAnimationAsset>(NULL,
				TEXT("/Game/PlayerCharacter/Hand2/2Handed_Idle.2Handed_Idle"), NULL, LOAD_None, NULL);
			iter->GetSkeletalMeshComponent()->SetAnimation(AssetAnim);
			iter->GetSkeletalMeshComponent()->PlayAnimation(AssetAnim, true);
			charaName = FText::FromString("Sword");
			break;
		}
		case 2:
		{
			TargetComponent = iter->GetSkeletalMeshComponent();
			UAnimationAsset* AssetAnim = LoadObject<UAnimationAsset>(NULL,
				TEXT("/Game/PlayerCharacter/Knight/Knight_Idle.Knight_Idle"), NULL, LOAD_None, NULL);
			iter->GetSkeletalMeshComponent()->SetAnimation(AssetAnim);
			iter->GetSkeletalMeshComponent()->PlayAnimation(AssetAnim, true);
			charaName = FText::FromString("Knight");
			break;
		}
		}

		break;
	}
	CLASSTB->SetText(charaName);
}

void UPCharaSelectWidget::OnPrevClicked()
{
	NextCharacter(false);
}

void UPCharaSelectWidget::OnNextClicked()
{
	NextCharacter(true);
}

void UPCharaSelectWidget::OnStartClicked()
{
	// 위에서 정한 캐릭터의 정보를 세이브 파일로 넘겨서 세이브 파일을 제작하고 게임을 시작하도록 만든다.
	USSaveGame* NewPlayerData = NewObject<USSaveGame>();
	NewPlayerData->PlayerName = charaName.ToString();
	NewPlayerData->Level = 1;
	NewPlayerData->Exp = 0;
	NewPlayerData->CharacterIDX = CurrentIDX;
	
	auto PState = GetDefault<APPlayerState>();
	if (UGameplayStatics::SaveGameToSlot(NewPlayerData, PState->SaveSlotName, 0)) // 세이브 파일을 불러오는데 없는 경우
	{
		UGameplayStatics::OpenLevel(GetWorld(), TEXT("PlayMap")); // 게임을 시작함
	}
	else
	{
		ABLOG(Error, TEXT("SaveGame Error")); // 로그를 찍는다.
	}
}
