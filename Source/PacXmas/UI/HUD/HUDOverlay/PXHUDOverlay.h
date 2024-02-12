// Copyright (c) 2023 Smoking Carrots. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PXHUDOverlay.generated.h"

class UPXClassSubsystem;
class UPXHeartTexturesDA;
class UPXScoreSubsystem;
class UPXDigitTextureManager;
class UHorizontalBox;

UCLASS()
class PACXMAS_API UPXHUDOverlay : public UUserWidget
{
	GENERATED_BODY()

public:
	void UpdateScore(const int32 Score);
	void UpdateHearts(const uint8_t Lives);

private:
	void InitializeDigitTextureManager();
	void InitializeClassSubsystem();

	void SetScoreInHorizontalBox(const int32 Score) const;
	void SetHeartsInHorizontalBox(const uint8_t Lives);

	UTexture2D* GetHeartTexture() const;

	FVector2D CharSize{32.f};
	FVector2D HeartSize{64.f};

	UPROPERTY(meta=(BindWidget))
	UHorizontalBox* ScoreHorizontalBox;
	UPROPERTY(meta=(BindWidget))
	UHorizontalBox* HeartsHorizontalBox;

	UPROPERTY(EditDefaultsOnly, Category="Managers")
	TSubclassOf<UPXDigitTextureManager> PXDigitTextureManagerClass;
	UPROPERTY()
	UPXDigitTextureManager* PXDigitTextureManager{nullptr};

	UPROPERTY(EditDefaultsOnly, Category="Data Assets|Textures|Hearts")
	UPXHeartTexturesDA* PXHeartTexturesDA{nullptr};

	UPROPERTY()
	UPXClassSubsystem* PXClassSubsystem{nullptr};
};
