// Copyright (c) 2023 Smoking Carrots. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PXGameModeGameplay.generated.h"

class APXPlayer;
class UPXSpawnItemsSubsystem;
class UPXClassSubsystem;
class UPXPlayerClassesDA;
class UPXItemClassesDA;

UCLASS()
class PACXMAS_API APXGameModeGameplay : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	virtual void BeginPlay() override;

	virtual void RestartPlayerAtPlayerStart(AController* NewPlayer, AActor* StartSpot) override;

public:
	// todo check why logic of respawning items are spread overall several classes
	void SpawnPuddingOnMap(const float SpawnDelay = 1) const;
	void SpawnMusicSheetOnMap() const;
	void SpawnAllFireworks() const;
	void RespawnFireworks(const FVector& SpawnLocation, const float SpawnDelay = 1) const;

private:
	void InitializeClassSubsystem();
	void InitializeSpawnItemsSubsystem();

	void BindHandleGameOver();
	UFUNCTION()
	void HandleGameOver();

	void OpenMenuLevel() const;

	UPROPERTY(EditDefaultsOnly, Category="Classes|Data Assets|Item")
	UPXItemClassesDA* PXItemClassesDA{nullptr};

	UPROPERTY(EditDefaultsOnly, Category="Classes|Data Assets|Player")
	UPXPlayerClassesDA* PXPlayerClassesDA{nullptr};

	UPROPERTY()
	UPXClassSubsystem* PXClassSubsystem{nullptr};
	UPROPERTY()
	UPXSpawnItemsSubsystem* PXSpawnItemsSubsystem{nullptr};

	UPROPERTY()
	APXPlayer* PXPlayer{nullptr};
};
