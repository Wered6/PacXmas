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
	void DrawLives(const uint8_t Lives) const;

	void ToggleLiveVisibility();

	UPROPERTY(EditDefaultsOnly, Category="HUD")
	UTexture2D* LiveTexture{nullptr};

	bool bIsLiveVisible{true};
	uint8_t BlinkCount{0};
	uint8_t MaxBlinkCount{6};
	FTimerHandle BlinkTimerHandle;
};
