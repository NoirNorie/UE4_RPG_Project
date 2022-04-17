// Fill out your copyright notice in the Description page of Project Settings.


#include "STitleWidget.h"
#include "Components/Button.h"
#include "SSaveGame.h"

void USTitleWidget::NativeConstruct()
{
	Super::NativeConstruct();

	BT_NewGame = Cast<UButton>(GetWidgetFromName(TEXT("BT_NewGame")));
	ABCHECK(BT_NewGame != nullptr);
	BT_NewGame->OnClicked.AddDynamic(this, &USTitleWidget::OnNewGameClicked);

	BT_Continue = Cast<UButton>(GetWidgetFromName(TEXT("BT_Continue")));
	ABCHECK(BT_Continue != nullptr);
	LoadGame = Cast<USSaveGame>(UGameplayStatics::LoadGameFromSlot("Player1", 0));
	if (IsValid(LoadGame)) // 세이브 파일이 존재하면 continue 버튼이 활성화된다.
	{
		UE_LOG(LogTemp, Log, TEXT("Save File Exist"));
		BT_Continue->SetIsEnabled(true);
		BT_Continue->OnClicked.AddDynamic(this, &USTitleWidget::OnContinueClicked);
	}
	else // 없으면 continue 버튼을 비활성화 한다.
	{
		BT_Continue->SetIsEnabled(false);
	}


	BT_Exit = Cast<UButton>(GetWidgetFromName(TEXT("BT_Exit")));
	ABCHECK(BT_Exit != nullptr);

	BT_Exit->OnClicked.AddDynamic(this, &USTitleWidget::OnExitClicked);
}

void USTitleWidget::OnNewGameClicked()
{
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("TitleSelect")); // 캐릭터 선택 화면으로 이동
}
void USTitleWidget::OnContinueClicked()
{
	// 세이브 파일을 가져와야 함
	UE_LOG(LogTemp, Log, TEXT("Load Check %s"), *LoadGame->PlayerName);
	LoadGame->PlayerName = TEXT("CHECK");
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("PlayMap")); // 캐릭터 선택 화면으로 이동
}
void USTitleWidget::OnExitClicked()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(),
		EQuitPreference::Quit, true);
}