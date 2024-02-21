// Copyright (c) 2023 Smoking Carrots. All rights reserved.


#include "PXEnemyMovementComponent.h"

void UPXEnemyMovementComponent::HandleMovement(float DeltaTime)
{
	// Handle ongoing movement
	Super::HandleMovement(DeltaTime);

	// Set CurrentDirection
	if (!bIsMoving)
	{
		const FVector NewDirection = ChooseNewAIDirection();
		TargetLocation = GetActorLocation() + NewDirection * TileSize;
		// Change CurrentDirection when NewDirection is different from CurrentDirection
		if (CurrentDirection != NewDirection)
		{
			CurrentDirection = NewDirection;
			UpdateRotation();
			UpdateFlipbook();
		}
		bIsMoving = true;
	}
}

FVector UPXEnemyMovementComponent::ChooseNewAIDirection() const
{
	TArray PossibleDirections =
	{
		FVector::ForwardVector,
		FVector::BackwardVector,
		FVector::UpVector,
		FVector::DownVector
	};
	// Remove opposite direction so no turning back
	PossibleDirections.Remove(-CurrentDirection);

	// Remove directions that are not possible to move in
	for (int8_t i = PossibleDirections.Num() - 1; i >= 0; --i)
	{
		if (!CanMoveInDirection(PossibleDirections[i]))
		{
			PossibleDirections.RemoveAt(i);
		}
	}

	// If there are no other options, allow turning back
	if (PossibleDirections.Num() <= 0)
	{
		PossibleDirections.Add(-CurrentDirection);
	}

	// Choose a random valid direction
	if (PossibleDirections.Num() > 0)
	{
		const uint8_t Choice = FMath::RandRange(0, PossibleDirections.Num() - 1);

		return PossibleDirections[Choice];
	}

	// Should never return
	return CurrentDirection;
}
