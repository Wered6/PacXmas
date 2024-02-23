// Copyright (c) 2023 Smoking Carrots. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PXPlayerControllerGameplay.generated.h"

class APXPlayer;

UCLASS()
class PACXMAS_API APXPlayerControllerGameplay : public APlayerController
{
	GENERATED_BODY()

public:
	APXPlayerControllerGameplay();

protected:
	virtual void BeginPlay() override;

public:
	void SetPlayerEnabledState(const bool bPlayerEnabled);

private:
	void InitializePlayer();

	UFUNCTION(BlueprintCallable)
	void MovePlayer(const FVector& Value);

	UFUNCTION(BlueprintCallable)
	void OnShootPuddingPressed();

	UPROPERTY()
	APXPlayer* PXPlayer{nullptr};
};
