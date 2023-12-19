// Copyright (c) 2023 Santa Claus. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PXCharacter.generated.h"

class UPXAppearanceComponent;
class UFloatingPawnMovement;
class UBoxComponent;

UCLASS()
class PACXMAS_API APXCharacter : public APawn
{
	GENERATED_BODY()

public:
	APXCharacter();

public:
	virtual void MoveHorizontal(const float Value);
	virtual void MoveVertical(const float Value);

protected:
	UPROPERTY(EditDefaultsOnly)
	UFloatingPawnMovement* FloatingPawnMovement{nullptr};
	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* CollisionComponent{nullptr};

private:
	const float CollisionWidth{31.f};
	const float CollisionDepth{31.f};
	const float CollisionHeight{31.f};
};
