// Copyright (c) 2023 Santa Claus. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PXGameModeGameplay.generated.h"

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

private:
	TSubclassOf<APXPlayer> GetPlayerClass() const;

	UPROPERTY(EditDefaultsOnly, Category="Player Classes|Boy")
	TSubclassOf<APXPlayer> BoyClass;
	UPROPERTY(EditDefaultsOnly, Category="Player Classes|Girl")
	TSubclassOf<APXPlayer> GirlClass;

	UPROPERTY(EditDefaultsOnly, Category="Items To Spawn|Pudding Class")
	TSubclassOf<APXPudding> PuddingClass;
};
