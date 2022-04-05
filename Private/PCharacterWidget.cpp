// Fill out your copyright notice in the Description page of Project Settings.


#include "PCharacterWidget.h"
#include "PCharacterStatComponent.h"
#include "Components/ProgressBar.h"

void UPCharacterWidget::BindCharacterStat(UPCharacterStatComponent* NewCharacterStat)
{
	ABCHECK(NewCharacterStat != nullptr);

	CurrentCharacterStat = NewCharacterStat;
	//NewCharacterStat->OnHPChanged.AddLambda([this]() -> void {
	//	if (CurrentCharacterStat.IsValid())
	//	{
	//		ABLOG(Warning, TEXT("HPRation : %f"), CurrentCharacterStat->GetHPRatio());
	//	}
	//});

	NewCharacterStat->OnHPChanged.AddUObject(this, &UPCharacterWidget::UpdateHPWidget);
}

void UPCharacterWidget::NativeConstruct()
{
	Super::NativeConstruct();
	HPProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("PB_HPBar")));
	ABCHECK(HPProgressBar != nullptr);
	UpdateHPWidget();
}

void UPCharacterWidget::UpdateHPWidget()
{
	if (CurrentCharacterStat.IsValid())
	{
		if (HPProgressBar != nullptr)
		{
			HPProgressBar->SetPercent(CurrentCharacterStat->GetHPRatio());
		}
	}
}