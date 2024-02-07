// Copyright (c) 2023 Smoking Carrots. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "PacXmas/UI/Menu/Widgets/BaseMenu/PXBaseMenuWidget.h"
#include "PXAudioSettingsWidget.generated.h"

class UPXAudioMixer;
class UPXAudioSubsystem;
class UTextBlock;
class USlider;

UCLASS()
class PACXMAS_API UPXAudioSettingsWidget : public UPXBaseMenuWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

protected:
	UFUNCTION(BlueprintCallable)
	void OnMusicSliderValueChanged();
	UFUNCTION(BlueprintCallable)
	void OnSFXSliderValueChanged();

	UFUNCTION(BlueprintCallable)
	void OnMusicVolumeMinusButtonClicked() const;
	UFUNCTION(BlueprintCallable)
	void OnSFXVolumeMinusButtonClicked() const;
	UFUNCTION(BlueprintCallable)
	void OnMusicVolumePlusButtonClicked() const;
	UFUNCTION(BlueprintCallable)
	void OnSFXVolumePlusButtonClicked() const;

	UPROPERTY(meta=(BindWidget))
	USlider* MusicSlider;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* MusicVolumeText;

	UPROPERTY(meta=(BindWidget))
	USlider* SFXSlider;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* SFXVolumeText;

private:
	void InitializeAudioMixer();

	void AdjustVolume(USlider* Slider, const float VolumeStep, const bool bIncrease) const;

	void ApplyVolumeChange(const USlider* Slider) const;
	
	void SetVolumeTextBasedOnSlider(const USlider* Slider, UTextBlock* VolumeText) const;

	void SaveAudioSettings() const;
	void LoadAudioSettings() const;

	const float MusicVolumeStep{.1f};
	const float SFXVolumeStep{.1f};

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UPXAudioMixer> PXAudioMixerClass;
	UPROPERTY()
	UPXAudioMixer* PXAudioMixer{nullptr};
};
