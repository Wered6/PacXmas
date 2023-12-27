// Copyright (c) 2023 Santa Claus. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PXGameModeGameplay.generated.h"

class APXFireworks;
class UPXSpawnItemsSubsystem;
class APXMusicSheet;
class APXPudding;
class UPXGameInstance;
class APXPlayer;

UCLASS()
class PACXMAS_API APXGameModeGameplay : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	virtual void RestartPlayerAtPlayerStart(AController* NewPlayer, AActor* StartSpot) override;

public:
	void SpawnPudding(const float SpawnDelay = 1) const;
	void SpawnMusicSheet() const;
	void SpawnAllFireworks() const;
	void RespawnFireworks(const FVector& SpawnLocation, const float SpawnDelay = 1) const;

private:
	TSubclassOf<APXPlayer> GetPlayerClass() const;

	void InitializePXSpawnItemsSubsystem();

	UPROPERTY(EditDefaultsOnly, Category="Player Classes|Boy")
	TSubclassOf<APXPlayer> BoyClass;
	UPROPERTY(EditDefaultsOnly, Category="Player Classes|Girl")
	TSubclassOf<APXPlayer> GirlClass;

	UPROPERTY(EditDefaultsOnly, Category="Items To Spawn|Pudding Class")
	TSubclassOf<APXPudding> PuddingClass;
	UPROPERTY(EditDefaultsOnly, Category="Items To Spawn|MusicSheet Class")
	TSubclassOf<APXMusicSheet> MusicSheetClass;
	UPROPERTY(EditDefaultsOnly, Category="Items To Spawn|Fireworks Class")
	TSubclassOf<APXFireworks> FireworksClass;

	UPROPERTY()
	UPXSpawnItemsSubsystem* PXSpawnItemsSubsystem{nullptr};
};
