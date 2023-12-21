// Copyright (c) 2023 Santa Claus. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PXHUD.generated.h"

UCLASS()
class PACXMAS_API APXHUD : public AHUD
{
	GENERATED_BODY()

public:
	virtual void DrawHUD() override;

	void StartHeartBlinking();

private:
	void DrawLives(const uint8_t Lives);

	void ToggleLifeVisibility();

	void SetLifeTexture();

	UPROPERTY(EditDefaultsOnly, Category="Lifes Textures|Girl")
	UTexture2D* LifeTextureGirl{nullptr};
	UPROPERTY(EditDefaultsOnly, Category="Lifes Textures|Boy")
	UTexture2D* LifeTextureBoy{nullptr};
	UPROPERTY()
	UTexture2D* ChosenLifeTexture{nullptr};

	bool bIsLifeVisible{true};
	uint8_t BlinkCount{0};
	uint8_t MaxBlinkCount{6};
	FTimerHandle BlinkTimerHandle;
};
