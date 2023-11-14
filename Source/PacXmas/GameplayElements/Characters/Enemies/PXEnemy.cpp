// Copyright (c) 2023 Santa Claus. All rights reserved.


#include "PXEnemy.h"

void APXEnemy::BeginPlay()
{
	Super::BeginPlay();

	ChangeDirection();

	MoveSpeed = 50.f;
}

void APXEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CanMoveInDirection(CurrentDirection, 16.f))
	{
		AddMovementInput(CurrentDirection, MoveSpeed * DeltaTime);
	}
	else
	{
		ChangeDirection();
	}
}

void APXEnemy::ChangeDirection()
{
	const int32 DirectionIndex = FMath::RandRange(0, 3);

	switch (DirectionIndex)
	{
	case 0:
		CurrentDirection = FVector::UpVector;
		break;
	case 1:
		CurrentDirection = FVector::ForwardVector;
		break;
	case 2:
		CurrentDirection = FVector::DownVector;
		break;
	case 3:
		CurrentDirection = FVector::BackwardVector;
		break;
	}
}

bool APXEnemy::CanMoveInDirection(const FVector& Direction, float Distance)
{
	FHitResult HitResult;
	FVector StartPosition = GetActorLocation();
	FVector EndPosition = StartPosition + Direction * Distance;

	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);

	bool bHit = GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartPosition,
		EndPosition,
		ECC_WorldDynamic,
		CollisionParams
	);

	return !bHit;
}
