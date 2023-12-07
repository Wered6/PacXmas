// Copyright (c) 2023 Santa Claus. All rights reserved.


#include "PXEnemy.h"
#include "BehaviorComponent/PXEnemyBehaviorComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "PacXmas/Utilities/CustomLogs/PXCustomLogs.h"

APXEnemy::APXEnemy()
{
	CollisionComponent->SetCollisionProfileName(TEXT("Enemy"));

	BehaviorComponent = CreateDefaultSubobject<UPXEnemyBehaviorComponent>(TEXT("BehaviorComponent"));

	if (!FloatingPawnMovement)
	{
		UE_LOG(LogCharacter, Warning, TEXT("APXEnemy::APXEnemy"))
		return;
	}

	FloatingPawnMovement->MaxSpeed = 200.f;
	FloatingPawnMovement->Acceleration = 20000.f;
	FloatingPawnMovement->Deceleration = 40000.f;
	FloatingPawnMovement->TurningBoost = 40.f;
}

void APXEnemy::BeginPlay()
{
	Super::BeginPlay();
}

void APXEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (BehaviorComponent && !bIsStunned)
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

FVector APXEnemy::GetScaledBoxExtent() const
{
	if (!CollisionComponent)
	{
		UE_LOG(LogCharacter, Warning, TEXT("APXEnemy::GetScaledBoxExtent|CollisionComponent is nullptr"))
		return FVector::ZeroVector;
	}

	return CollisionComponent->GetScaledBoxExtent();
}

void APXEnemy::EatPudding()
{
	StunYourself(EatingPuddingTime);
	// todo implement changing flipbooks and not being able to overlap PXPlayer
}

void APXEnemy::GetFlashed()
{
	StunYourself(FlashedTime);
	// todo implement changing flipbooks and not being able to overlap PXPlayer
}

void APXEnemy::StunYourself(const float Time)
{
	bIsStunned = true;

	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &APXEnemy::ResetStun, Time);
}

void APXEnemy::ResetStun()
{
	bIsStunned = false;
}
