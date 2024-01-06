// Copyright (c) 2023 Santa Claus. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "PXLevelSubsystem.generated.h"

class UPXMenuManager;

UCLASS()
class PACXMAS_API UPXLevelSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	// USubsystem implementation Begin
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	// USubsystem implementation End

	void CompleteLevel();

	bool GetCompletedAllLevels() const;

	void SetGameStarted(const bool GameStarted);
	bool GetGameStarted() const;
	
private:
	void InitializeLevelNamesArray();

	uint8_t CurrentLevelIndex{0};
	TArray<FName> LevelNames;

	bool bNewHighScore{false};
	
	bool bGameStarted{false};
	
	bool bInitialized{false};
};
