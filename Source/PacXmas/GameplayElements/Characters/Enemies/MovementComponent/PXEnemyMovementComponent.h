// Copyright (c) 2023 Smoking Carrots. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "PacXmas/GameplayElements/Characters/MovementComponent/PXCharacterMovementComponent.h"
#include "PXEnemyMovementComponent.generated.h"

UCLASS()
class PACXMAS_API UPXEnemyMovementComponent : public UPXCharacterMovementComponent
{
	GENERATED_BODY()

public:

protected:
	virtual void HandleMovement(float DeltaTime) override;

private:
	FVector ChooseNewAIDirection() const;
};
