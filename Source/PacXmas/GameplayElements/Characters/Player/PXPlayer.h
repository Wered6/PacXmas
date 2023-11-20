// Copyright (c) 2023 Santa Claus. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PacXmas/GameplayElements/Characters/PXCharacter.h"
#include "PXPlayer.generated.h"

UCLASS()
class PACXMAS_API APXPlayer : public APXCharacter
{
	GENERATED_BODY()

public:
	APXPlayer();
	
	virtual void Tick(float DeltaSeconds) override;

	virtual void MoveHorizontal(const float Value) override;
	virtual void MoveVertical(const float Value) override;

private:
	bool bIsPlayerInputActive{false};
};
