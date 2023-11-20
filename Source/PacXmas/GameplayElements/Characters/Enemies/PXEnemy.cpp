// Copyright (c) 2023 Santa Claus. All rights reserved.


#include "PXEnemy.h"
#include "BehaviorComponent/PXEnemyBehaviorComponent.h"
#include "DrawDebugHelpers.h"
#include "Components/BoxComponent.h"
#include "GameFramework/FloatingPawnMovement.h"

APXEnemy::APXEnemy()
{
	CollisionComp->SetCollisionProfileName(TEXT("Enemy"));

	BehaviorComponent = CreateDefaultSubobject<UPXEnemyBehaviorComponent>(TEXT("BehaviorComponent"));

	if (FloatingPawnMovement)
	{
		FloatingPawnMovement->MaxSpeed = 200.f;
		FloatingPawnMovement->Acceleration = 10000.f;
		FloatingPawnMovement->Deceleration = 20000.f;
		FloatingPawnMovement->TurningBoost = 20.f;
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
