// Copyright (c) 2023 Smoking Carrots. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PXGameModeMenu.generated.h"

class UPXAudioMixer;
class UPXScoreSubsystem;
class UPXLevelSubsystem;
class UPXMenuManager;

UCLASS()
class PACXMAS_API APXGameModeMenu : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	void InitializeAudioMixer();
	void InitializeMenuManager();
	void InitializeLevelSubsystem();
	void InitializeScoreSubsystem();

	void LoadAudioSettings() const;
	
	void OpenAppropriateWidget() const;

	void UpdateHighScores() const;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UPXAudioMixer> PXAudioMixerClass;
	UPROPERTY()
	UPXAudioMixer* PXAudioMixer{nullptr};
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UPXMenuManager> PXMenuManagerClass;
	UPROPERTY()
	UPXMenuManager* PXMenuManager{nullptr};

	UPROPERTY()
	UPXLevelSubsystem* PXLevelSubsystem{nullptr};
	UPROPERTY()
	UPXScoreSubsystem* PXScoreSubsystem{nullptr};
};
