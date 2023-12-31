// Copyright (c) 2023 Santa Claus. All rights reserved.


#include "PXPlayerMovementComponent.h"
#include "PacXmas/GameplayElements/Characters/Player/PXPlayer.h"

UPXPlayerMovementComponent::UPXPlayerMovementComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	TileSize = DefaultTileSize;
	MovementSpeed = DefaultMovementSpeed;
	bIsMoving = false;
	DesiredDirection = FVector::ZeroVector;
	CurrentDirection = DesiredDirection;
}

void UPXPlayerMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	TargetLocation = PawnOwner->GetActorLocation();
}

void UPXPlayerMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                               FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!PawnOwner || !UpdatedComponent || ShouldSkipUpdate(DeltaTime))
	{
		return;
	}

	// Handle the ongoing movement
	if (bIsMoving)
	{
		MoveInDirection(CurrentDirection, DeltaTime);
		if (HasReachedTileBorder())
		{
			PawnOwner->SetActorLocation(TargetLocation);
			bIsMoving = false;
		}
	}

	// Check for queued turns at decision points
	if (!bIsMoving && !NextDesiredDirection.IsZero() && CanMoveInDirection(NextDesiredDirection))
	{
		if (HasReachedDecisionPoint())
		{
			DesiredDirection = NextDesiredDirection;
			NextDesiredDirection = FVector::ZeroVector;

			bIsMoving = true;
			TargetLocation = PawnOwner->GetActorLocation() + DesiredDirection * TileSize;
			CurrentDirection = DesiredDirection;
		}
	}
	// Handle initial movement if not already moving
	else if (!bIsMoving && !DesiredDirection.IsZero() && CanMoveInDirection(DesiredDirection))
	{
		bIsMoving = true;
		TargetLocation = PawnOwner->GetActorLocation() + DesiredDirection * TileSize;
		CurrentDirection = DesiredDirection;
	}
}

void UPXPlayerMovementComponent::SetDesiredDirection(const FVector& NewDirection)
{
	NextDesiredDirection = NewDirection;
}

bool UPXPlayerMovementComponent::HasReachedDecisionPoint() const
{
	if (!PawnOwner)
	{
		UE_LOG(LogActor, Warning, TEXT("UPXPlayerMovementComponent::HasReachedDecisionPoint|PawnOwner is nullptr"))
		return false;
	}

	const FVector CurrentLocation = PawnOwner->GetActorLocation();

	// Calculate how close we are to being aligned with the grid
	const float ModX = FMath::Fmod(CurrentLocation.X, TileSize);
	const float ModY = FMath::Fmod(CurrentLocation.Y, TileSize);
	const float Threshold = TileSize * 0.01f; // Threshold for grid alignment

	// Check if the player is close to being aligned with the grid
	const bool bIsAlignedX = FMath::IsNearlyZero(ModX, Threshold);
	const bool bIsAlignedY = FMath::IsNearlyZero(ModY, Threshold);

	return bIsAlignedX || bIsAlignedY;
}

bool UPXPlayerMovementComponent::CanMoveInDirection(const FVector& Direction) const
{
	if (!PawnOwner)
	{
		UE_LOG(LogActor, Warning, TEXT("UPXPlayerMovementComponent::CanMoveInDirection|PawnOwner is nullptr"))
		return false;
	}

	const APXPlayer* PXPlayer = Cast<APXPlayer>(PawnOwner);

	FHitResult HitResult;
	const FVector StartPosition = PXPlayer->GetActorLocation();
	const FVector EndPosition = StartPosition + Direction * MoveCheckDistance;

	FCollisionShape CollisionShape;
	CollisionShape.SetBox(FVector3f(PXPlayer->GetScaledBoxExtent()));
	FCollisionQueryParams CollisionQueryParams;

	bool bHit = GetWorld()->SweepSingleByChannel(
		HitResult,
		StartPosition,
		EndPosition,
		FQuat::Identity,
		ECC_GameTraceChannel11,
		CollisionShape,
		CollisionQueryParams
	);

	return !bHit;
}


bool UPXPlayerMovementComponent::HasReachedTileBorder() const
{
	if (!PawnOwner)
	{
		UE_LOG(LogActor, Warning, TEXT("UPXPlayerMovementComponent::HasReachedTileBorder|PawnOwner is nullptr"))
		return false;
	}

	const FVector CurrentLocation = PawnOwner->GetActorLocation();
	const FVector DirectionToTarget = (TargetLocation - CurrentLocation).GetSafeNormal();
	const FVector CurrentMoveDirection = CurrentDirection.GetSafeNormal();

	if (FVector::DotProduct(DirectionToTarget, CurrentMoveDirection) < 0)
	{
		return true;
	}

	const float DistanceToTarget = FVector::Dist(CurrentLocation, TargetLocation);
	return DistanceToTarget < BorderProximityThreshold;
}

void UPXPlayerMovementComponent::MoveInDirection(const FVector& Direction, const float DeltaTime)
{
	const FVector ActorLocation = PawnOwner->GetActorLocation();
	const FVector NewLocation = ActorLocation + (MovementSpeed * DeltaTime * Direction);

	const FVector MoveDistance = NewLocation - ActorLocation;
	const FRotator ActorRotation = PawnOwner->GetActorRotation();

	MoveUpdatedComponent(MoveDistance, ActorRotation, true);
}
