// Copyright (c) 2023 Santa Claus. All rights reserved.


#include "PXCharacterMovementComponent.h"
#include "PacXmas/GameplayElements/Characters/PXCharacter.h"
#include "PacXmas/GameplayElements/Characters/Enemies/PXEnemy.h"
#include "PacXmas/GameplayElements/Characters/Player/PXPlayer.h"
#include "PacXmas/Utilities/CustomLogs/PXCustomLogs.h"

UPXCharacterMovementComponent::UPXCharacterMovementComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	TileSize = DefaultTileSize;
	MovementSpeed = DefaultMovementSpeed;
	bIsMoving = bDefaultIsMoving;
	DesiredDirection = DefaultDesiredDirection;
	CurrentDirection = DefaultCurrentDirection;

	// AI
	bIsAIControlled = bDefaultIsAIControlled;
	AccumulatedTime = DefaultAccumulatedTime;
	DecisionInterval = DefaultDecisionInterval;
	bCanAIMove = bDefaultCanAIMove;
}

void UPXCharacterMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	if (!PawnOwner)
	{
		UE_LOG(LogOwner, Warning, TEXT("UPXCharacterMovementComponent::BeginPlay|PawnOwner is nullptr"))
		return;
	}

	TargetLocation = PawnOwner->GetActorLocation();
}

void UPXCharacterMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                                  FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (ShouldSkipUpdate(DeltaTime))
	{
		return;
	}

	// Handle AI-controlled movement
	if (bIsAIControlled)
	{
		if (bCanAIMove)
		{
			HandleAIMovement(DeltaTime);
		}
	}
	else
	{
		HandlePlayerMovement(DeltaTime);
	}

	ResetTargetLocationIfTooFar();
}

void UPXCharacterMovementComponent::SetDesiredDirection(const FVector& NewDirection)
{
	NextDesiredDirection = NewDirection;
}

bool UPXCharacterMovementComponent::GetIsMoving() const
{
	return bIsMoving;
}

void UPXCharacterMovementComponent::ResetTargetLocationIfTooFar()
{
	if (FVector::Dist(PawnOwner->GetActorLocation(), TargetLocation) > TileSize)
	{
		TargetLocation = GetActorLocation();
	}
}

void UPXCharacterMovementComponent::SetIsAIControlled(const bool bNewValue)
{
	bIsAIControlled = bNewValue;
}

void UPXCharacterMovementComponent::SetCanAIMove(const bool bNewValue)
{
	bCanAIMove = bNewValue;
}

bool UPXCharacterMovementComponent::GetCanAIMove() const
{
	return bCanAIMove;
}

bool UPXCharacterMovementComponent::HasReachedDecisionPoint() const
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

bool UPXCharacterMovementComponent::CanMoveInDirection(const FVector& Direction) const
{
	if (!PawnOwner)
	{
		UE_LOG(LogActor, Warning, TEXT("UPXPlayerMovementComponent::CanMoveInDirection|PawnOwner is nullptr"))
		return false;
	}

	const APXCharacter* PXCharacter = Cast<APXCharacter>(PawnOwner);

	if (!PXCharacter)
	{
		UE_LOG(LogActor, Warning, TEXT("UPXCharacterMovementComponent::CanMoveInDirection|PXCharacter is nullptr"))
		return false;
	}

	FHitResult HitResult;

	const FVector StartPosition = PXCharacter->GetActorLocation();

	const FVector EndPosition = StartPosition + Direction * MoveCheckDistance;

	ECollisionChannel CollisionChannel = GetCollisionChannelBasedOnOwnerClass();

	FCollisionShape CollisionShape;
	CollisionShape.SetBox(FVector3f(PXCharacter->GetScaledBoxExtent()));

	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.AddIgnoredActor(PawnOwner);

	bool bHit = GetWorld()->SweepSingleByChannel(
		HitResult,
		StartPosition,
		EndPosition,
		FQuat::Identity,
		CollisionChannel,
		CollisionShape,
		CollisionQueryParams
	);

	return !bHit;
}

bool UPXCharacterMovementComponent::HasReachedTileBorder() const
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

void UPXCharacterMovementComponent::MoveInDirection(const FVector& Direction, const float DeltaTime)
{
	if (!PawnOwner)
	{
		UE_LOG(LogActor, Warning, TEXT("UPXPlayerMovementComponent::MoveInDirection|PawnOwner is nullptr"))
		return;
	}

	const FVector ActorLocation = PawnOwner->GetActorLocation();
	const FVector NewLocation = ActorLocation + (MovementSpeed * DeltaTime * Direction);
	const FVector MoveDistance = NewLocation - ActorLocation;

	// Calculate the new rotation based on the movement direction
	if (!Direction.IsNearlyZero())
	{
		const FRotator NewRotation = Direction.Rotation();
		PawnOwner->SetActorRotation(NewRotation);
	}

	const FRotator ActorRotation = PawnOwner->GetActorRotation();
	MoveUpdatedComponent(MoveDistance, ActorRotation, true);
}

ECollisionChannel UPXCharacterMovementComponent::GetCollisionChannelBasedOnOwnerClass() const
{
	if (!PawnOwner)
	{
		UE_LOG(LogOwner, Warning,
		       TEXT("UPXCharacterMovementComponent::GetCollisionChannelBasedOnOwnerClass|PawnOwner is nullptr"))
		return ECC_EngineTraceChannel1;
	}

	if (PawnOwner->GetClass()->IsChildOf(APXPlayer::StaticClass()))
	{
		return ECC_GameTraceChannel11;
	}
	if (PawnOwner->GetClass()->IsChildOf(APXEnemy::StaticClass()))
	{
		return ECC_GameTraceChannel8;
	}

	return ECC_GameTraceChannel1;
}

void UPXCharacterMovementComponent::HandlePlayerMovement(float DeltaTime)
{
	if (!PawnOwner)
	{
		UE_LOG(LogOwner, Warning, TEXT("UPXCharacterMovementComponent::HandlePlayerMovement|PawnOwner is nullptr"))
		return;
	}

	// Handle ongoing movement
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

void UPXCharacterMovementComponent::HandleAIMovement(float DeltaTime)
{
	if (!PawnOwner)
	{
		UE_LOG(LogOwner, Warning, TEXT("UPXCharacterMovementComponent::HandleAIMovement|PawnOwner is nullptr"))
		return;
	}

	// Handle ongoing movement
	if (bIsMoving)
	{
		MoveInDirection(CurrentDirection, DeltaTime);
		if (HasReachedTileBorder())
		{
			PawnOwner->SetActorLocation(TargetLocation);
			bIsMoving = false;
		}
	}
	else
	{
		CurrentDirection = ChooseNewAIDirection();
		TargetLocation = PawnOwner->GetActorLocation() + CurrentDirection * TileSize;
		bIsMoving = true;
	}
}

FVector UPXCharacterMovementComponent::ChooseNewAIDirection() const
{
	TArray<FVector> PossibleDirections =
	{
		FVector::ForwardVector,
		FVector::BackwardVector,
		FVector::UpVector,
		FVector::DownVector
	};
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
	if (PossibleDirections.Num() == 0)
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
