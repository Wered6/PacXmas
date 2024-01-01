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
	FVector GetScaledBoxExtent() const;

protected:
	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* CollisionComponent{nullptr};

	float CollisionSize{31.f};
};
