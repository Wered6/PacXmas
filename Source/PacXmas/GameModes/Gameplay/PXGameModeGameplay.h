// Copyright (c) 2023 Santa Claus. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PXGameModeGameplay.generated.h"

class UPXGameInstance;
class APXPlayer;

UCLASS()
class PACXMAS_API APXGameModeGameplay : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void RestartPlayerAtPlayerStart(AController* NewPlayer, AActor* StartSpot) override;

private:
	TSubclassOf<APXPlayer> GetPlayerClass() const;

	UPROPERTY(EditDefaultsOnly, Category="Player Classes|Boy")
	TSubclassOf<APXPlayer> BoyClass;
	UPROPERTY(EditDefaultsOnly, Category="Player Classes|Girl")
	TSubclassOf<APXPlayer> GirlClass;
};
