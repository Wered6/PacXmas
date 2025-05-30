// Copyright (c) 2023 Smoking Carrots. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PXCharacter.generated.h"

class UPXCharacterMovementComponent;
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
	float CollisionSize{31.f};

	UPROPERTY()
	UBoxComponent* CollisionComponent{nullptr};
};
