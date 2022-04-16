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
	if (Asset != nullptr) TargetComponent->SetSkeletalMesh(Asset);
}

void UPCharaSelectWidget::NativeConstruct()
{
	Super::NativeConstruct();

	CurrentIDX = 0;
	auto CharaSetting = GetDefault<UPCharacterSetting>();
	MaxIDX = CharaSetting->CharacterAssets.Num();

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
	USSaveGame* NewPlayerData = NewObject<USSaveGame>();
	NewPlayerData->PlayerName = TEXT("Knight");
	NewPlayerData->Level = 1;
	NewPlayerData->Exp = 0;
	
	auto PState = GetDefault<APPlayerState>();
	if (UGameplayStatics::SaveGameToSlot(NewPlayerData, PState->SaveSlotName, 0))
	{
		UGameplayStatics::OpenLevel(GetWorld(), TEXT("PlayMap")); // 게임을 시작함
	}
	else
	{
		ABLOG(Error, TEXT("SaveGame Error"));
	}
}
