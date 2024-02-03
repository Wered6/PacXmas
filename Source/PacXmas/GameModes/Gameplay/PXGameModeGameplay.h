// Copyright (c) 2023 Smoking Carrots. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PXGameModeGameplay.generated.h"

class UPXPlayerClassManager;
class UPXClassSubsystem;
class UPXSpawnItemsSubsystem;
class APXFireworks;
class APXMusicSheet;
class APXPudding;
class APXPlayer;

UCLASS()
class PACXMAS_API APXGameModeGameplay : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	virtual void BeginPlay() override;

	virtual void RestartPlayerAtPlayerStart(AController* NewPlayer, AActor* StartSpot) override;

public:
	void SpawnPuddingOnMap(const float SpawnDelay = 1) const;
	void SpawnMusicSheetOnMap() const;
	void SpawnAllFireworks() const;
	void RespawnFireworks(const FVector& SpawnLocation, const float SpawnDelay = 1) const;

private:
	void InitializePlayerClassManager();
	void InitializeClassSubsystem();
	void InitializeSpawnItemsSubsystem();

	void BindHandleGameOver();
	UFUNCTION()
	void HandleGameOver();

	void OpenMenuLevel() const;
	
	UPROPERTY(EditDefaultsOnly, Category="Items To Spawn|Pudding Class")
	TSubclassOf<APXPudding> PuddingClass;
	UPROPERTY(EditDefaultsOnly, Category="Items To Spawn|MusicSheet Class")
	TSubclassOf<APXMusicSheet> MusicSheetClass;
	UPROPERTY(EditDefaultsOnly, Category="Items To Spawn|Fireworks Class")
	TSubclassOf<APXFireworks> FireworksClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UPXPlayerClassManager> PXPlayerClassManagerClass;
	UPROPERTY()
	UPXPlayerClassManager* PXPlayerClassManager{nullptr};

	UPROPERTY()
	UPXClassSubsystem* PXClassSubsystem{nullptr};
	UPROPERTY()
	UPXSpawnItemsSubsystem* PXSpawnItemsSubsystem{nullptr};

	UPROPERTY()
	APXPlayer* PXPlayer{nullptr};
};
