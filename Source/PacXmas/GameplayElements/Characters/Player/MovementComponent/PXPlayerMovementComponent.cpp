// Copyright (c) 2023 Smoking Carrots. All rights reserved.


#include "PXPlayerMovementComponent.h"
#include "PacXmas/Utilities/CustomLogs/PXCustomLogs.h"

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
			TargetLocation = GetActorLocation() + DesiredDirection * TileSize;
			// Change CurrentDirection when DesiredDirection is different from CurrentDirection
			if (CurrentDirection != DesiredDirection)
			{
				CurrentDirection = DesiredDirection;
				UpdateFlipbook();
				UpdateRotation();
			}
		}
		else
		{
			if (bFirstStop)
			{
				SetFlipbookIdle();
				bFirstStop = false;
			}
		}
	}
	ResetTargetLocationWhenTeleport();
}

void UPXPlayerMovementComponent::ResetTargetLocationWhenTeleport()
{
	if (FVector::Dist(GetActorLocation(), TargetLocation) > TileSize)
	{
		// When teleport reset TargetLocation
		TargetLocation = GetActorLocation();
	}
}

void UPXPlayerMovementComponent::SetFlipbookIdle() const
{
	if (!OnStopMoving.ExecuteIfBound())
	{
		UE_LOG(LogDelegate, Warning, TEXT("UPXPlayerMovementComponent::SetFlipbookIdle|OnStopMoving not bound"))
	}
}
