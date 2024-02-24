// Copyright (c) 2023 Smoking Carrots. All rights reserved.


#include "PXDeathMessageWidget.h"
#include "Components/BackgroundBlur.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "PacXmas/Utilities/CustomLogs/PXCustomLogs.h"

void UPXDeathMessageWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	// Opacity is 0 to 1
	const float OpacityValue = PassedTime / MessageTime;
	PassedTime += InDeltaTime;

	SetBackgroundBlurOpacity(OpacityValue);
	SetBackgroundColorOpacity(OpacityValue);
	SetDeathTextOpacity(OpacityValue);

	if (PassedTime >= MessageTime)
	{
		RemoveFromParent();
	}
}

void UPXDeathMessageWidget::SetBackgroundBlurOpacity(const float Value) const
{
	if (!BackgroundBlur)
	{
		UE_LOG(LogWidget, Warning, TEXT("UPXDeathMessageWidget::SetBackgroundBlurOpacity|BackgroundBlur is nullptr"))
		return;
	}

	BackgroundBlur->SetRenderOpacity(Value);
}

void UPXDeathMessageWidget::SetBackgroundColorOpacity(const float Value) const
{
	if (!BackgroundColor)
	{
		UE_LOG(LogWidget, Warning, TEXT("UPXDeathMessageWidget::SetBackgroundColorOpacity|BackgroundColor is nullptr"))
		return;
	}

	BackgroundColor->SetRenderOpacity(Value);
}

void UPXDeathMessageWidget::SetDeathTextOpacity(const float Value) const
{
	if (!DeathText)
	{
		UE_LOG(LogWidget, Warning, TEXT("UPXDeathMessageWidget::SetDeathTextOpacity|DeathText is nullptr"))
		return;
	}

	DeathText->SetRenderOpacity(Value);
}
