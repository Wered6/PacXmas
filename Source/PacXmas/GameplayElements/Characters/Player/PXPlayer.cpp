// Copyright (c) 2023 Santa Claus. All rights reserved.


#include "PXPlayer.h"

#include "Components/BoxComponent.h"

APXPlayer::APXPlayer()
{
	CollisionComp->SetCollisionProfileName(TEXT("Player"));
}

void APXPlayer::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (!bIsPlayerInputActive && GetVelocity().IsNearlyZero())
	{
		SetFlipbookToIdle();
	}

	bIsPlayerInputActive = false;
}

void APXPlayer::MoveHorizontal(const float Value)
{
	if (Value != 0)
	{
		bIsPlayerInputActive = true;

		Super::MoveHorizontal(Value);
	}
}

void APXPlayer::MoveVertical(const float Value)
{
	if (Value != 0)
	{
		bIsPlayerInputActive = true;

		Super::MoveVertical(Value);
	}
}
