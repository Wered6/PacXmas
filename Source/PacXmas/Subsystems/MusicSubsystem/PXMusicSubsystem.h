// Copyright (c) 2023 Santa Claus. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "PXMusicSubsystem.generated.h"

class USoundCue;

UCLASS()
class PACXMAS_API UPXMusicSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	void PlayRandomBackgroundMusic();
	void PlayRandomVictoryMusic();
	void PlayRandomLostMusic();
	void StopMusic();

private:
	void PlayMusic(USoundCue* MusicCue);
	USoundCue* GetRandomCue(const TArray<USoundCue*>& Cues);

	UPROPERTY(EditDefaultsOnly, Category="Music|Background")
	TArray<USoundCue*> BackgroundMusicCues;
	UPROPERTY(EditDefaultsOnly, Category="Music|Won")
	TArray<USoundCue*> WonMusicCues;
	UPROPERTY(EditDefaultsOnly, Category="Music|Lost")
	TArray<USoundCue*> LostMusicCues;

	UPROPERTY()
	UAudioComponent* CurrentAudioComponent{nullptr};
};
