// Fill out your copyright notice in the Description page of Project Settings.


#include "PUpgradeWidgetBT.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

void UPUpgradeWidgetBT::NativeConstruct()
{
	Super::NativeConstruct();

	BT_Right = Cast<UButton>(GetWidgetFromName(TEXT("BT_Right")));
	IG_RightImg = Cast<UImage>(GetWidgetFromName(TEXT("IG_RightImg")));
	TB_RightEX = Cast<UTextBlock>(GetWidgetFromName(TEXT("BT_Right")));

	BT_Left = Cast<UButton>(GetWidgetFromName(TEXT("BT_Right")));
	IG_LeftImg = Cast<UImage>(GetWidgetFromName(TEXT("BT_Right")));
	TB_LeftEX = Cast<UTextBlock>(GetWidgetFromName(TEXT("BT_Right")));
}