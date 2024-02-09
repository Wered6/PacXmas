// Copyright (c) 2023 Smoking Carrots. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PXHUD.generated.h"

class UPXScorePopup;
enum class EScoreTypes;
class UPXLifeTextureManager;
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

	void DisplayScorePopup(const EScoreTypes ScoreType);

private:
	void InitializeScorePopupWidget();
	void InitializeLifeTextureManager();
	void InitializeDigitTextureManager();
	void InitializeScoreSubsystem();

	void DrawLives() const;
	void DrawScore() const;

	// DrawLives methods
	UTexture2D* GetLifeTexture() const;
	uint8_t GetLives() const;

	// DrawScore methods
	UTexture2D* GetDigitTexture(const int32 Digit) const;
	int32 GetScore() const;

	void ToggleLifeVisibility();
	UFUNCTION()
	void StartLifeBlinking();
	void BindLifeBlinking();

	bool bIsLifeVisible{true};
	uint8_t BlinkCount{0};
	uint8_t MaxBlinkCount{6};
	FTimerHandle BlinkTimerHandle;

	UPROPERTY(EditDefaultsOnly, Category="Widgets|Score Popup")
	TSubclassOf<UPXScorePopup> PXScorePopupClass;
	UPROPERTY()
	UPXScorePopup* PXScorePopup{nullptr};

	UPROPERTY(EditDefaultsOnly, Category="Managers|Life Textures")
	TSubclassOf<UPXLifeTextureManager> PXLifeTextureManagerClass;
	UPROPERTY()
	UPXLifeTextureManager* PXLifeTextureManager{nullptr};

	UPROPERTY(EditDefaultsOnly, Category="Managers|Digit Textures")
	TSubclassOf<UPXDigitTextureManager> PXDigitTextureManagerClass;
	UPROPERTY()
	UPXDigitTextureManager* PXDigitTextureManager{nullptr};

	UPROPERTY()
	UPXScoreSubsystem* PXScoreSubsystem{nullptr};
	//todo create widget to add score and lives
};
