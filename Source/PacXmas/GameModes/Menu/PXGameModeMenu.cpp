// Copyright (c) 2023 Smoking Carrots. All rights reserved.


#include "PXGameModeMenu.h"
#include "PacXmas/GameInstance/PXGameInstance.h"
#include "PacXmas/Subsystems/AudioSubsystem/PXAudioMixer.h"
#include "PacXmas/Subsystems/LevelSubsystem/PXLevelSubsystem.h"
#include "PacXmas/Subsystems/ScoreSubsystem/PXScoreSubsystem.h"
#include "PacXmas/UI/Menu/MenuManager/PXMenuManager.h"
#include "PacXmas/Utilities/CustomLogs/PXCustomLogs.h"

void APXGameModeMenu::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	InitializeAudioMixer();
	InitializeMenuManager();
	InitializeLevelSubsystem();
	InitializeScoreSubsystem();
}

void APXGameModeMenu::BeginPlay()
{
	Super::BeginPlay();

	LoadAudioSettings();

	OpenAppropriateWidget();

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

void APXGameModeMenu::InitializeMenuManager()
{
	if (!PXMenuManagerClass)
	{
		UE_LOG(LogMenuManager, Warning, TEXT("APXGameModeMenu::InitializePXMenuManager|PXMenuManagerClass is nullptr"))
		return;
	}

	PXMenuManager = NewObject<UPXMenuManager>(this, PXMenuManagerClass);
}

void APXGameModeMenu::InitializeLevelSubsystem()
{
	const UPXGameInstance* PXGameInstance = Cast<UPXGameInstance>(GetGameInstance());

	if (!PXGameInstance)
	{
		UE_LOG(LogGameInstance, Warning, TEXT("APXGameModeMenu::InitializePXLevelSubsystem|PXGameInstance is nullptr"))
		return;
	}

	PXLevelSubsystem = PXGameInstance->GetSubsystem<UPXLevelSubsystem>();
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

void APXGameModeMenu::OpenAppropriateWidget() const
{
	if (!PXMenuManager)
	{
		UE_LOG(LogMenuManager, Warning, TEXT("APXGameModeMenu::OpenAppropriateWidget|PXMenuManager is nullptr"))
		return;
	}
	if (!PXLevelSubsystem)
	{
		UE_LOG(LogSubsystem, Warning, TEXT("APXGameModeMenu::OpenAppropriateWidget|PXLevelSubsystem is nullptr"))
		return;
	}
	if (!PXScoreSubsystem)
	{
		UE_LOG(LogSubsystem, Warning, TEXT("APXGameModeMenu::OpenAppropriateWidget|PXScoreSubsystem is nullptr"))
		return;
	}

	const bool bGameStarted = PXLevelSubsystem->HasGameStarted();
	const bool bHighScoreBeaten = PXScoreSubsystem->IsHighScoreBeaten();

	if (!bGameStarted)
	{
		PXMenuManager->OpenMainMenuWidget();
		PXLevelSubsystem->SetGameStarted(true);
	}
	else
	{
		if (bHighScoreBeaten)
		{
			PXMenuManager->OpenCelebrationWidget();
		}
		else
		{
			PXMenuManager->OpenEndGameWidget();
		}
	}
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
