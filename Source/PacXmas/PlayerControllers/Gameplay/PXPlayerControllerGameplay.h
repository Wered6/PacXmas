// Copyright (c) 2023 Santa Claus. All rights reserved.

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
	virtual void SetupInputComponent() override;

private:
	void MovePlayerHorizontal(const float Value);
	void MovePlayerVertical(const float Value);

	void OnShootPuddingPressed();
	
	UPROPERTY()
	APXPlayer* PXPlayer{nullptr};
};
