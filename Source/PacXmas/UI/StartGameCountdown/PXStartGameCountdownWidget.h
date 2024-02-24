// Copyright (c) 2023 Smoking Carrots. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PXStartGameCountdownWidget.generated.h"

class UBackgroundBlur;
class UTextBlock;

UCLASS()
class PACXMAS_API UPXStartGameCountdownWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:
	void SetBackgroundBlurOpacity(const float Value) const;
	void StartCountdown();

	UPROPERTY(meta=(BindWidget))
	UBackgroundBlur* BackgroundBlur{nullptr};
	UPROPERTY(meta=(BindWidget))
	UTextBlock* CountdownText{nullptr};
	
	float Countdown{2.f};
};
