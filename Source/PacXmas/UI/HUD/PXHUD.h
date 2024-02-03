// Copyright (c) 2023 Smoking Carrots. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PXHUD.generated.h"

class UPXClassSubsystem;
class UPXDigitTextureManager;
class UPXScoreSubsystem;

UCLASS()
class PACXMAS_API APXHUD : public AHUD
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	virtual void DrawHUD() override;

private:
	void InitializeDigitTextureManager();
	void InitializeScoreSubsystem();
	void InitializeClassSubsystem();

	void DrawScore() const;
	void DrawLives();

	// DrawLives methods
	void SetLifeTexture();
	void ToggleLifeVisibility();
	UFUNCTION()
	void StartLifeBlinking();
	void BindLifeBlinking();

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

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UPXDigitTextureManager> PXDigitTextureManagerClass;
	UPROPERTY()
	UPXDigitTextureManager* PXDigitTextureManager{nullptr};

	UPROPERTY()
	UPXScoreSubsystem* PXScoreSubsystem{nullptr};
	UPROPERTY()
	UPXClassSubsystem* PXClassSubsystem{nullptr};
	//todo create widget to add score and lives
};
