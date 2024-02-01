// Copyright (c) 2023 Smoking Carrots. All rights reserved.


#include "PXAudioMixer.h"
#include "Kismet/GameplayStatics.h"
#include "PacXmas/SaveGame/AudioSettings/PXAudioSettingsSaveGame.h"
#include "PacXmas/Utilities/CustomLogs/PXCustomLogs.h"
#include "Sound/SoundClass.h"
#include "Sound/SoundMix.h"

void UPXAudioMixer::SetMusicSoundClassVolume(const float MusicVolume) const
{
	SetSoundClassVolume(PXMusicSoundClass, MusicVolume);
}

void UPXAudioMixer::SetSFXSoundClassVolume(const float SFXVolume) const
{
	SetSoundClassVolume(PXSFXSoundClass, SFXVolume);
}

void UPXAudioMixer::SaveAudioSettings(const float MusicVolume, const float SFXVolume) const
{
	UPXAudioSettingsSaveGame* SaveGameInstance = Cast<UPXAudioSettingsSaveGame>(
		UGameplayStatics::CreateSaveGameObject(UPXAudioSettingsSaveGame::StaticClass()));

	if (!SaveGameInstance)
	{
		UE_LOG(LogSaveGame, Warning, TEXT("UPXAudioMixer::SaveAudioSettings|SaveGameInstance is nullptr"))
		return;
	}

	SaveGameInstance->MusicVolume = MusicVolume;
	SaveGameInstance->SFXVolume = SFXVolume;

	UGameplayStatics::SaveGameToSlot(SaveGameInstance, TEXT("AudioSettings"), 0);
}

void UPXAudioMixer::LoadAudioSettings(float& MusicVolumeOUT, float& SFXVolumeOUT) const
{
	if (UGameplayStatics::DoesSaveGameExist(TEXT("AudioSettings"), 0))
	{
		const UPXAudioSettingsSaveGame* LoadGameInstance = Cast<UPXAudioSettingsSaveGame>(
			UGameplayStatics::LoadGameFromSlot(TEXT("AudioSettings"), 0));

		if (!LoadGameInstance)
		{
			UE_LOG(LogSaveGame, Warning, TEXT("UPXAudioMixer::LoadAudioSettings|LoadGameInstance is nullptr"))
			return;
		}

		MusicVolumeOUT = LoadGameInstance->MusicVolume;
		SFXVolumeOUT = LoadGameInstance->SFXVolume;
	}
}

void UPXAudioMixer::SetSoundClassVolume(USoundClass* SoundClass, const float Volume) const
{
	if (!PXGameSoundMix)
	{
		UE_LOG(LogSound, Warning, TEXT("UPXAudioMixer::SetSoundClassVolume|PXGameSoundMix is nullptr"))
		return;
	}
	if (!SoundClass)
	{
		UE_LOG(LogSound, Warning, TEXT("UPXAudioMixer::SetSoundClassVolume|SoundClass is nullptr"))
		return;
	}

	UGameplayStatics::SetSoundMixClassOverride(this, PXGameSoundMix, SoundClass, Volume, 1.f, 0.f);
	UGameplayStatics::PushSoundMixModifier(this, PXGameSoundMix);
}
