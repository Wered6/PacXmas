// Copyright (c) 2023 Smoking Carrots. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PXHUDOverlay.generated.h"

class UPXScoreSubsystem;
class UPXDigitTextureManager;
class UHorizontalBox;

UCLASS()
class PACXMAS_API UPXHUDOverlay : public UUserWidget
{
	GENERATED_BODY()

public:
	void UpdateScore(const int32 Score);
	
private:
	void InitializeDigitTextureManager();

	void SetScoreInHorizontalBox(const int32 Score) const;

	FVector2D CharSize{32.f};
	
	UPROPERTY(meta=(BindWidget))
	UHorizontalBox* ScoreHorizontalBox;
	UPROPERTY(meta=(BindWidget))
	UHorizontalBox* HeartsHorizontalBox;
	
	UPROPERTY(EditDefaultsOnly, Category="Managers")
	TSubclassOf<UPXDigitTextureManager> PXDigitTextureManagerClass;
	UPROPERTY()
	UPXDigitTextureManager* PXDigitTextureManager{nullptr};
};
