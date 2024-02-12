// Copyright (c) 2023 Smoking Carrots. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PXHUD.generated.h"

class UPXClassSubsystem;
class UPXScoreSubsystem;
class UPXHeartTexturesDA;
class UPXScorePopup;
class UPXHUDOverlay;
enum class EScoreTypes;

UCLASS()
class PACXMAS_API APXHUD : public AHUD
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	virtual void DrawHUD() override;

	void UpdateScore() const;

	void DisplayScorePopup(const EScoreTypes ScoreType);

private:
	void InitializeHUDOverlayWidget();
	void InitializeScorePopupWidget();
	void InitializeScoreSubsystem();
	void InitializeClassSubsystem();

	void AddHUDOverlayToTheViewport() const;

	void DrawLives() const;

	// DrawLives methods
	UTexture2D* GetHeartTexture() const;
	uint8_t GetLives() const;
	
	void ToggleLifeVisibility();
	UFUNCTION()
	void StartLifeBlinking();
	void BindLifeBlinking();

	bool bIsLifeVisible{true};
	uint8_t BlinkCount{0};
	uint8_t MaxBlinkCount{6};
	FTimerHandle BlinkTimerHandle;

	UPROPERTY(EditDefaultsOnly, Category="Widgets|HUD Overlay")
	TSubclassOf<UPXHUDOverlay> PXHUDOverlayClass;
	UPROPERTY()
	UPXHUDOverlay* PXHUDOverlay{nullptr};
	
	UPROPERTY(EditDefaultsOnly, Category="Widgets|Score Popup")
	TSubclassOf<UPXScorePopup> PXScorePopupClass;
	UPROPERTY()
	UPXScorePopup* PXScorePopup{nullptr};

	UPROPERTY(EditDefaultsOnly, Category="Data Assets|Textures|Hearts")
	UPXHeartTexturesDA* PXHeartTexturesDA{nullptr};
	
	UPROPERTY()
	UPXScoreSubsystem* PXScoreSubsystem{nullptr};
	UPROPERTY()
	UPXClassSubsystem* PXClassSubsystem{nullptr};
	//todo create widget to add score and lives
};
