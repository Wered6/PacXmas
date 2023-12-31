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

	if (!bIsMoving && !DesiredDirection.IsZero() && CanMoveInDirection(DesiredDirection))
	{
		bIsMoving = true;
		TargetLocation = UpdatedComponent->GetComponentLocation() + DesiredDirection * TileSize;
		CurrentDirection = DesiredDirection;
	}

	if (bIsMoving)
	{
		MoveInDirection(CurrentDirection, DeltaTime);
	}

	if (HasReachedTileBorder())
	{
		PawnOwner->SetActorLocation(TargetLocation);
		bIsMoving = false;
	}

	UE_LOG(LogTemp, Warning, TEXT("ActorLocation: %s"), *PawnOwner->GetActorLocation().ToString())
	UE_LOG(LogTemp, Warning, TEXT("DesiredDirection: %s"), *DesiredDirection.ToString())
	UE_LOG(LogTemp, Warning, TEXT("TargetLocation: %s"), *TargetLocation.ToString())
	UE_LOG(LogTemp, Warning, TEXT("CurrentDirection: %s"), *CurrentDirection.ToString())
	if (bIsMoving)
	{
		UE_LOG(LogTemp, Warning, TEXT("bIsMoving: true"))
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("bIsMoving: false"))
	}
}

void UPXPlayerMovementComponent::SetDesiredDirection(const FVector& NewDirection)
{
	DesiredDirection = NewDirection;
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
