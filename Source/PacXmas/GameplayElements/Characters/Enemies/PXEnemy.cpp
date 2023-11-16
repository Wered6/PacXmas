// Copyright (c) 2023 Santa Claus. All rights reserved.


#include "PXEnemy.h"
#include "BehaviorComponent/PXEnemyBehaviorComponent.h"
#include "Components/BoxComponent.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/FloatingPawnMovement.h"

APXEnemy::APXEnemy()
{
	BehaviorComponent = CreateDefaultSubobject<UPXEnemyBehaviorComponent>(TEXT("BehaviorComponent"));

	if (FloatingPawnMovement)
	{
		FloatingPawnMovement->MaxSpeed = 200.f;
	}
}

void APXEnemy::BeginPlay()
{
	Super::BeginPlay();
}

void APXEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (BehaviorComponent)
	{
		const FVector Direction = BehaviorComponent->DetermineNextDirection();
		if (Direction.Equals(FVector::UpVector) || Direction.Equals(FVector::DownVector))
		{
			MoveVertical(Direction.Z);
		}
		else if (Direction.Equals(FVector::ForwardVector) || Direction.Equals(FVector::BackwardVector))
		{
			MoveHorizontal(Direction.X);
		}
	}
}

bool APXEnemy::CanMoveInDirection(const FVector& Direction, float Distance) const
{
	if (!GetWorld())
	{
		return false;
	}

	FHitResult HitResult;
	FVector StartPosition = GetActorLocation();
	FVector EndPosition = StartPosition + Direction * Distance;

	FCollisionShape CollisionShape;
	float Offset{0.5f};
	CollisionShape.SetBox(FVector3f(GetCollisionComp()->GetScaledBoxExtent() - Offset));

	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);

	bool bHit = GetWorld()->SweepSingleByChannel(
		HitResult,
		StartPosition,
		EndPosition,
		FQuat::Identity,
		ECC_WorldStatic,
		CollisionShape,
		CollisionParams
	);

	if (GEngine)
	{
		DrawDebugBox(
			GetWorld(),
			EndPosition,
			CollisionShape.GetExtent(),
			FQuat::Identity,
			bHit ? FColor::Red : FColor::Green,
			false,
			0.1f,
			0,
			1.0f
		);
	}

	return !bHit;
}
