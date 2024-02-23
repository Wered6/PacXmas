// Copyright (c) 2023 Smoking Carrots. All rights reserved.


#include "PXStartGameWidget.h"

#include "Components/TextBlock.h"
#include "Kismet/KismetMathLibrary.h"

void UPXStartGameWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	StartCountdown(InDeltaTime);
}

void UPXStartGameWidget::StartCountdown(const float InDeltaTime)
{
	Countdown -= InDeltaTime;

	const int32 CeiledCountdown = UKismetMathLibrary::FCeil(Countdown);

	switch (CeiledCountdown)
	{
	case 0:
		{
			CountdownText->SetText(FText::AsNumber(1));
			break;
		}
	case 1:
		{
			CountdownText->SetText(FText::AsNumber(2));
			break;
		}
	case 2:
		{
			CountdownText->SetText(FText::AsNumber(3));
			break;
		}
	default:
		{
			RemoveFromParent();
		}
	}
}
