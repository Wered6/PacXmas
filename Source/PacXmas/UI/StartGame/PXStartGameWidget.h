// Copyright (c) 2023 Smoking Carrots. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PXStartGameWidget.generated.h"

class UTextBlock;

UCLASS()
class PACXMAS_API UPXStartGameWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:
	void StartCountdown(const float InDeltaTime);
	
	UPROPERTY(meta=(BindWidget))
	UTextBlock* CountdownText{nullptr};
	
	float Countdown{2.f};
};
