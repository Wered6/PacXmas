// Copyright (c) 2023 Smoking Carrots. All rights reserved.


#include "PXCharacterMovementComponent.h"
#include "PacXmas/GameplayElements/Characters/PXCharacter.h"
#include "PacXmas/GameplayElements/Characters/Enemies/PXEnemy.h"
#include "PacXmas/GameplayElements/Characters/Player/PXPlayer.h"
#include "PacXmas/Utilities/CustomLogs/PXCustomLogs.h"

UPXCharacterMovementComponent::UPXCharacterMovementComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UPXCharacterMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	TargetLocation = GetActorLocation();
}

void UPXCharacterMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                                  FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bCanMove)
	{
		HandleMovement(DeltaTime);
	}

	ResetTargetLocationIfTooFar();
}

bool UPXCharacterMovementComponent::GetIsMoving() const
{
	return bIsMoving;
}

void UPXCharacterMovementComponent::SetCanMove(const bool bNewValue)
{
	bCanMove = bNewValue;
}

bool UPXCharacterMovementComponent::GetCanMove() const
{
	return bCanMove;
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

void UPXCharacterMovementComponent::HandleMovement(float DeltaTime)
{
	if (!PawnOwner)
	{
		UE_LOG(LogOwner, Warning, TEXT("UPXCharacterMovementComponent::HandleMovement|PawnOwner is nullptr"))
		return;
	}

	// Handle ongoing movement
	if (bIsMoving)
	{
		MoveInDirection(CurrentDirection, DeltaTime);
		// If moved to TargetLocation
		if (HasReachedTargetLocation())
		{
			// Ensure that Pawn is exactly on grid
			PawnOwner->SetActorLocation(TargetLocation);
			// Reached TargetLocation so let's reset CurrentDirection
			bIsMoving = false;
		}
	}
}

bool UPXCharacterMovementComponent::HasReachedTargetLocation() const
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

void UPXCharacterMovementComponent::ResetTargetLocationIfTooFar()
{
	if (FVector::Dist(PawnOwner->GetActorLocation(), TargetLocation) > TileSize)
	{
		TargetLocation = GetActorLocation();
	}
}
