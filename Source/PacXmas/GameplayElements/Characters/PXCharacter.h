// Copyright (c) 2023 Santa Claus. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PXCharacter.generated.h"

UCLASS()
class PACXMAS_API APXCharacter : public APawn
{
	GENERATED_BODY()

public:
	APXCharacter();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void MoveHorizontal(const float Value);
	virtual void MoveVertical(const float Value);
};
