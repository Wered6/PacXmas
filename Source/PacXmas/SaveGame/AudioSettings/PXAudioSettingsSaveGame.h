// Copyright (c) 2023 Smoking Carrots. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "PXAudioSettingsSaveGame.generated.h"

UCLASS()
class PACXMAS_API UPXAudioSettingsSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY()
	float MusicVolume{1.f};
	UPROPERTY()
	float SFXVolume{1.f};
};
