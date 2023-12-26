// Copyright (c) 2023 Santa Claus. All rights reserved.


#include "PXLevelSubsystem.h"
#include "Kismet/GameplayStatics.h"

void UPXLevelSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	check(!bInitialized);
	bInitialized = true;

	InitializeLevelNamesArray();
}

void UPXLevelSubsystem::Deinitialize()
{
	check(bInitialized);
	bInitialized = false;
}

void UPXLevelSubsystem::CompleteLevel()
{
	CurrentLevelIndex++;

	if (LevelNames.IsValidIndex(CurrentLevelIndex))
	{
		UGameplayStatics::OpenLevel(this, LevelNames[CurrentLevelIndex]);
	}
}

void UPXLevelSubsystem::InitializeLevelNamesArray()
{
	LevelNames.Add(FName("Level1"));
	LevelNames.Add(FName("Level2"));
	LevelNames.Add(FName("Level3"));
	LevelNames.Add(FName("Level4"));
	LevelNames.Add(FName("Level5"));
	LevelNames.Add(FName("Level6"));
}
