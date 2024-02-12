// Copyright (c) 2023 Smoking Carrots. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PXScorePopup.generated.h"

class UPXDigitTextureManager;
class UHorizontalBox;

UCLASS()
class PACXMAS_API UPXScorePopup : public UUserWidget
{
	GENERATED_BODY()

public:
	void Play(const int32 Score, const APlayerController* PlayerController);

private:
	void InitializeDigitTextureManager();

	void SetScoreInHorizontalBox(const int32 Score) const;
	void SetPositionInViewport(const APlayerController* PlayerController);

	void PlayFadingUpAnimation();
	void SetTimerRemoveFromParent();

	FVector2D CharSize{16.f};

	UPROPERTY(meta=(BindWidget))
	UHorizontalBox* ScoreHorizontalBox;

	UPROPERTY(Transient, meta=(BindWidgetAnim))
	UWidgetAnimation* FadingUp;

	UPROPERTY(EditDefaultsOnly, Category="Managers")
	TSubclassOf<UPXDigitTextureManager> PXDigitTextureManagerClass;
	UPROPERTY()
	UPXDigitTextureManager* PXDigitTextureManager{nullptr};
};
