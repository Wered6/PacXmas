// Copyright (c) 2023 Smoking Carrots. All rights reserved.

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
	void PlayCelebrationMusic();
	UFUNCTION(BlueprintCallable)
	void PlayEndGameMusic();
	UFUNCTION(BlueprintCallable)
	void StopMusic();

private:
	void PlayMusic(USoundCue* MusicCue);

	UPROPERTY(EditDefaultsOnly, Category="Music")
	USoundCue* BackgroundMusicCue;
	UPROPERTY(EditDefaultsOnly, Category="Music")
	USoundCue* LostMusicCue;
	UPROPERTY(EditDefaultsOnly, Category="Music")
	USoundCue* WonMusicCue;

	UPROPERTY()
	UAudioComponent* CurrentAudioComponent{nullptr};
};
