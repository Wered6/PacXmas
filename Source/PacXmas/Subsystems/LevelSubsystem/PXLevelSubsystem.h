// Copyright (c) 2023 Santa Claus. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "PXLevelSubsystem.generated.h"

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

private:
	void InitializeLevelNamesArray();

	uint8_t CurrentLevelIndex{0};
	TArray<FName> LevelNames;

	bool bInitialized{false};
};
