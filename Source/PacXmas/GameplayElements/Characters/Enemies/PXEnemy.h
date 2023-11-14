// Copyright (c) 2023 Santa Claus. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PacXmas/GameplayElements/Characters/PXCharacter.h"
#include "PXEnemy.generated.h"

UCLASS()
class PACXMAS_API APXEnemy : public APXCharacter
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

private:
	void ChangeDirection();
	bool CanMoveInDirection(const FVector& Direction, float Distance);

	FVector CurrentDirection{FVector::ZeroVector};
	float MoveSpeed{0};
};
