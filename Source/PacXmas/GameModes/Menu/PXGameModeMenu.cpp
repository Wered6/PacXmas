// Copyright (c) 2023 Smoking Carrots. All rights reserved.


#include "PXGameModeMenu.h"
#include "PacXmas/GameInstance/PXGameInstance.h"
#include "PacXmas/Subsystems/AudioSubsystem/PXAudioMixer.h"
#include "PacXmas/Subsystems/ScoreSubsystem/PXScoreSubsystem.h"
#include "PacXmas/Utilities/CustomLogs/PXCustomLogs.h"

void APXGameModeMenu::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	InitializeAudioMixer();
	InitializeScoreSubsystem();
}

void APXGameModeMenu::BeginPlay()
{
	Super::BeginPlay();

	LoadAudioSettings();

	UpdateHighScores();
}

void APXGameModeMenu::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (!PXScoreSubsystem)
	{
		UE_LOG(LogSubsystem, Warning, TEXT("APXGameModeMenu::EndPlay|PXScoreSubsystem is nullptr"))
		return;
	}

	PXScoreSubsystem->ResetScore();
}

void APXGameModeMenu::InitializeAudioMixer()
{
	if (!PXAudioMixerClass)
	{
		UE_LOG(LogSound, Warning, TEXT("APXGameModeMenu::|PXAudioMixerClass is nullptr"))
		return;
	}

	PXAudioMixer = NewObject<UPXAudioMixer>(this, PXAudioMixerClass);
}

void APXGameModeMenu::InitializeScoreSubsystem()
{
	const UPXGameInstance* PXGameInstance = Cast<UPXGameInstance>(GetGameInstance());

	if (!PXGameInstance)
	{
		UE_LOG(LogGameInstance, Warning, TEXT("APXGameModeMenu::InitializePXScoreSubsystem|PXGameInstance is nullptr"))
		return;
	}

	PXScoreSubsystem = PXGameInstance->GetSubsystem<UPXScoreSubsystem>();
}

void APXGameModeMenu::LoadAudioSettings() const
{
	if (!PXAudioMixer)
	{
		UE_LOG(LogSound, Warning, TEXT("APXGameModeMenu::LoadAudioSettings|PXAudioMixer is nullptr"))
		return;
	}

	float MusicVolume{100.f};
	float SFXVolume{100.f};

	PXAudioMixer->LoadAudioSettings(MusicVolume, SFXVolume);

	PXAudioMixer->SetMusicSoundClassVolume(MusicVolume);
	PXAudioMixer->SetSFXSoundClassVolume(SFXVolume);
}

void APXGameModeMenu::UpdateHighScores() const
{
	if (!PXScoreSubsystem)
	{
		UE_LOG(LogSubsystem, Warning, TEXT("APXGameModeMenu::OpenHighScores|PXScoreSubsystem is nullptr"))
		return;
	}

	PXScoreSubsystem->UpdateHighScores();
}
