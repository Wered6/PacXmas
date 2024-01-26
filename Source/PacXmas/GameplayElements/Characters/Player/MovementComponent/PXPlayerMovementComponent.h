// Copyright (c) 2023 Smoking Carrots. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "PacXmas/GameplayElements/Characters/MovementComponent/PXCharacterMovementComponent.h"
#include "PXPlayerMovementComponent.generated.h"

UCLASS()
class PACXMAS_API UPXPlayerMovementComponent : public UPXCharacterMovementComponent
{
	GENERATED_BODY()

public:
	void SetNextDesiredDirection(const FVector& NewDirection);

private:
	virtual void HandleMovement(float DeltaTime) override;
	
	FVector DesiredDirection{FVector::ZeroVector};
	FVector NextDesiredDirection{FVector::ZeroVector};
};
