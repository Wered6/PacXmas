// Copyright (c) 2023 Smoking Carrots. All rights reserved.


#include "PXStartGameCountdownWidget.h"
#include "Components/BackgroundBlur.h"
#include "Components/TextBlock.h"
#include "Kismet/KismetMathLibrary.h"
#include "PacXmas/Utilities/CustomLogs/PXCustomLogs.h"

void UPXStartGameCountdownWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	// Opacity is 0 to 1
	const float OpacityValue = (1.f + Countdown) / 3.f;
	Countdown -= InDeltaTime;
	
	SetBackgroundBlurOpacity(OpacityValue);

	StartCountdown();
}

void UPXStartGameCountdownWidget::SetBackgroundBlurOpacity(const float Value) const
{
	if (!BackgroundBlur)
	{
		UE_LOG(LogWidget, Warning,
		       TEXT("UPXStartGameCountdownWidget::SetBackgroundBlurOpacity|BackgroundBlur is nullptr"))
		return;
	}

	BackgroundBlur->SetRenderOpacity(Value);
}

void UPXStartGameCountdownWidget::StartCountdown()
{
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
