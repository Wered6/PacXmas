// Copyright (c) 2023 Smoking Carrots. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PXScorePopup.generated.h"

class UPXDigitTexturesDA;
class UHorizontalBox;

UCLASS()
class PACXMAS_API UPXScorePopup : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetScoreToPopup(const int32 Score);
	void PlayFadingUpAnimation();

private:
	void AddSignTexture(const bool bPositive);
	void AddDigitsTextures(const int32 Score);

	TArray<int32> ConvertScoreIntoArray(const int32 Score) const;
	void AddChildToHorizontalBox(UTexture2D* Texture);

	void SetTimerRemoveFromParent();

	FVector2D CharSize{16.f};

	UPROPERTY(meta=(BindWidget))
	UHorizontalBox* ScoreHorizontalBox;

	UPROPERTY(Transient, meta=(BindWidgetAnim))
	UWidgetAnimation* FadingUp;

	UPROPERTY(EditDefaultsOnly, Category="Data Assets|Textures|Digits")
	UPXDigitTexturesDA* PXDigitTexturesDA{nullptr};
};
