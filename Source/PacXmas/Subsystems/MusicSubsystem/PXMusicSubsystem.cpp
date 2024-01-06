// Copyright (c) 2023 Santa Claus. All rights reserved.


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
	PlayMusic(GetRandomCue(WonMusicCues));
}

void UPXMusicSubsystem::PlayLostMusic()
{
	PlayMusic(GetRandomCue(LostMusicCues));
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

USoundCue* UPXMusicSubsystem::GetRandomCue(const TArray<USoundCue*>& Cues) const
{
	if (Cues.Num() > 0)
	{
		const int8_t Index = FMath::RandRange(0, Cues.Num() - 1);
		return Cues[Index];
	}
	return nullptr;
}
