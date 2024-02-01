// Copyright (c) 2023 Smoking Carrots. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "PXAudioMixer.generated.h"

class USlider;

UCLASS(Blueprintable)
class PACXMAS_API UPXAudioMixer : public UObject
{
	GENERATED_BODY()

public:
	void SetMusicSoundClassVolume(const float MusicVolume) const;
	void SetSFXSoundClassVolume(const float SFXVolume) const;

	void SaveAudioSettings(const float MusicVolume, const float SFXVolume) const;
	void LoadAudioSettings(float& MusicVolumeOUT, float& SFXVolumeOUT) const;

private:
	void SetSoundClassVolume(USoundClass* SoundClass, const float Volume) const;

	UPROPERTY(EditDefaultsOnly, Category="Audio|Music")
	USoundClass* PXMusicSoundClass{nullptr};
	UPROPERTY(EditDefaultsOnly, Category="Audio|SFX")
	USoundClass* PXSFXSoundClass{nullptr};
	UPROPERTY(EditDefaultsOnly, Category="Audio|Mix")
	USoundMix* PXGameSoundMix{nullptr};
};
