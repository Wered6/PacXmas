// Copyright (c) 2023 Smoking Carrots. All rights reserved.


#include "PXMusicSubsystem.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PacXmas/Utilities/CustomLogs/PXCustomLogs.h"
#include "Sound/SoundCue.h"

void UPXMusicSubsystem::PlayBackgroundMusic()
{
	PlayMusic(BackgroundMusicCue);
}

void UPXMusicSubsystem::PlayWonMusic()
{
	PlayMusic(WonMusicCue);
}

void UPXMusicSubsystem::PlayLostMusic()
{
	PlayMusic(LostMusicCue);
}

void UPXMusicSubsystem::StopMusic()
{
	if (!CurrentAudioComponent)
	{
		UE_LOG(LogComponent, Warning, TEXT("UPXMusicSubsystem::StopMusic|CurrentAudioComponent is nullptr"))
		return;
	}

	CurrentAudioComponent->Stop();
	CurrentAudioComponent = nullptr;
}

void UPXMusicSubsystem::PlayMusic(USoundCue* MusicCue)
{
	if (!MusicCue)
	{
		UE_LOG(LogMusicCue, Warning, TEXT("UPXMusicSubsystem::PlayMusic|MusicCue is nullptr"))
		return;
	}

	if (CurrentAudioComponent && CurrentAudioComponent->IsPlaying())
	{
		CurrentAudioComponent->Stop();
	}

	CurrentAudioComponent = UGameplayStatics::SpawnSound2D(this, MusicCue, 1.f, 1.f, 0.f, nullptr, true);
}
