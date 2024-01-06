// Copyright (c) 2023 Santa Claus. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "PXMusicSubsystem.generated.h"

class USoundCue;

UCLASS(Blueprintable)
class PACXMAS_API UPXMusicSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void PlayBackgroundMusic();
	UFUNCTION(BlueprintCallable)
	void PlayWonMusic();
	UFUNCTION(BlueprintCallable)
	void PlayLostMusic();
	UFUNCTION(BlueprintCallable)
	void StopMusic();

private:
	void PlayMusic(USoundCue* MusicCue);
	USoundCue* GetRandomCue(const TArray<USoundCue*>& Cues) const;

	UPROPERTY(EditDefaultsOnly, Category="Music")
	USoundCue* BackgroundMusicCue;
	UPROPERTY(EditDefaultsOnly, Category="Music")
	TArray<USoundCue*> LostMusicCues;
	UPROPERTY(EditDefaultsOnly, Category="Music")
	TArray<USoundCue*> WonMusicCues;

	UPROPERTY()
	UAudioComponent* CurrentAudioComponent{nullptr};
};
