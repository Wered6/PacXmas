// Copyright (c) 2023 Santa Claus. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "PXSpawnItemsSubsystem.generated.h"

class APXMusicSheetSpawnPoint;
class APXPuddingSpawnPoint;
class APXFireworks;
class APXMusicSheet;
class APXPudding;

UCLASS()
class PACXMAS_API UPXSpawnItemsSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	virtual void OnWorldBeginPlay(UWorld& InWorld) override;

	void SpawnMusicSheet(TSubclassOf<APXMusicSheet> MusicSheetClass);
	void SpawnPudding(const TSubclassOf<APXPudding> PuddingClass, const float SpawnDelay);
	void SpawnFireworks();

private:
	void InitializePuddingSpawnPointsArray();
	void InitializeMusicSheetPointsArray();

	UFUNCTION()
	void DelayedSpawnPudding(const TSubclassOf<APXPudding> PuddingClass, const FVector& SpawnLocation);

	uint8_t MusicSheetSpawnedCount{0};
	
	TArray<APXPuddingSpawnPoint*> PuddingSpawnPoints;
	TArray<APXMusicSheetSpawnPoint*> MusicSheetSpawnPoints;
};
