// Copyright (c) 2023 Smoking Carrots. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PXHUD.generated.h"

class UPXScoreSubsystem;
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
	void UpdateScore() const;
	UFUNCTION()
	void UpdateHearts();

	void DisplayScorePopup(const EScoreTypes ScoreType);

private:
	void InitializeHUDOverlayWidget();
	void InitializeScorePopupWidget();
	void InitializeScoreSubsystem();

	void AddHUDOverlayToTheViewport() const;

	uint8_t GetLives() const;

	void BindUpdateHearts();

	UPROPERTY(EditDefaultsOnly, Category="Widgets|HUD Overlay")
	TSubclassOf<UPXHUDOverlay> PXHUDOverlayClass;
	UPROPERTY()
	UPXHUDOverlay* PXHUDOverlay{nullptr};

	UPROPERTY(EditDefaultsOnly, Category="Widgets|Score Popup")
	TSubclassOf<UPXScorePopup> PXScorePopupClass;
	UPROPERTY()
	UPXScorePopup* PXScorePopup{nullptr};

	UPROPERTY()
	UPXScoreSubsystem* PXScoreSubsystem{nullptr};
};
