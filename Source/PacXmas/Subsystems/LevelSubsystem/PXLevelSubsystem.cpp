// Copyright (c) 2023 Smoking Carrots. All rights reserved.


#include "PXLevelSubsystem.h"
#include "Kismet/GameplayStatics.h"

void UPXLevelSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	check(!bInitialized);
	bInitialized = true;

	InitializeLevelNamesArray();

	bHasGameStarted = false;
}

void UPXLevelSubsystem::Deinitialize()
{
	check(bInitialized);
	bInitialized = false;
}

void UPXLevelSubsystem::OpenRandomLevel()
{
	if (LevelNames.Num() > 0)
	{
		const int8_t RandomIndex = FMath::RandRange(0, LevelNames.Num() - 1);
		const FName LevelName = LevelNames[RandomIndex];
		UGameplayStatics::OpenLevel(this, LevelName);
	}
}

void UPXLevelSubsystem::SetHasGameStarted(const bool GameStarted)
{
	bHasGameStarted = GameStarted;
}

bool UPXLevelSubsystem::GetHasGameStarted() const
{
	return bHasGameStarted;
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
