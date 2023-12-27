// Copyright (c) 2023 Santa Claus. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "PXSpawnItemsSubsystem.generated.h"

class APXFireworksSpawnPoint;
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

	void SpawnPudding(const TSubclassOf<APXPudding> PuddingClass, const float SpawnDelay);
	void SpawnMusicSheet(const TSubclassOf<APXMusicSheet> MusicSheetClass);
	void SpawnAllFireworks(const TSubclassOf<APXFireworks> FireworksClass);
	void RespawnFireworks(const TSubclassOf<APXFireworks> FireworksClass, const float SpawnDelay,
	                      const FVector& SpawnLocation);

private:
	void InitializePuddingSpawnPointsArray();
	void InitializeMusicSheetSpawnPointsArray();
	void InitializeFireworksSpawnPointsArray();

	UFUNCTION()
	void DelayedSpawnPudding(const TSubclassOf<APXPudding> PuddingClass, const FVector& SpawnLocation);
	UFUNCTION()
	void DelayedSpawnFireworks(const TSubclassOf<APXFireworks> FireworksClass, const FVector& SpawnLocation);

	uint8_t MusicSheetSpawnedCount{0};

	TArray<APXPuddingSpawnPoint*> PuddingSpawnPoints;
	TArray<APXMusicSheetSpawnPoint*> MusicSheetSpawnPoints;
	TArray<APXFireworksSpawnPoint*> FireworksSpawnPoints;
};
