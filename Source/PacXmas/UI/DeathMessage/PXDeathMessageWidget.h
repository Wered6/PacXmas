// Copyright (c) 2023 Smoking Carrots. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PXDeathMessageWidget.generated.h"

class UBackgroundBlur;
class UImage;
class UTextBlock;

UCLASS()
class PACXMAS_API UPXDeathMessageWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:
	void SetBackgroundBlurOpacity(const float Value) const;
	void SetBackgroundColorOpacity(const float Value) const;
	void SetDeathTextOpacity(const float Value) const;
	
	float PassedTime{0.f};
	float MessageTime{3.1f};

	UPROPERTY(meta=(BindWidget))
	UBackgroundBlur* BackgroundBlur{nullptr};
	UPROPERTY(meta=(BindWidget))
	UImage* BackgroundColor{nullptr};
	UPROPERTY(meta=(BindWidget))
	UTextBlock* DeathText{nullptr};
};
