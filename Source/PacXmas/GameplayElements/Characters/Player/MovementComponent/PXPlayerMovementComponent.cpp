// Copyright (c) 2023 Smoking Carrots. All rights reserved.


#include "PXPlayerMovementComponent.h"

void UPXPlayerMovementComponent::SetNextDesiredDirection(const FVector& NewDirection)
{
	NextDesiredDirection = NewDirection;
}

void UPXPlayerMovementComponent::HandleMovement(float DeltaTime)
{
	// Handle ongoing movement
	Super::HandleMovement(DeltaTime);

	// Set CurrentDirection
	if (!bIsMoving)
	{
		// If can move in queued direction, set new direction
		if (!NextDesiredDirection.IsZero() && CanMoveInDirection(NextDesiredDirection))
		{
			// Set DesiredDirection as queued direction and reset NextDesiredDirection
			DesiredDirection = NextDesiredDirection;
			NextDesiredDirection = FVector::ZeroVector;

			bIsMoving = true;
		}
		// If cant move in queued direction, leave old direction
		else if (!DesiredDirection.IsZero() && CanMoveInDirection(DesiredDirection))
		{
			bIsMoving = true;
		}

		// If set any direction, set new TargetLocation and CurrentDirection
		if (bIsMoving)
		{
			TargetLocation = PawnOwner->GetActorLocation() + DesiredDirection * TileSize;
			CurrentDirection = DesiredDirection;
		}
	}
}
