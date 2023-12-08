// Copyright (c) 2023 Santa Claus. All rights reserved.


#include "PXPlayer.h"
#include "Components/BoxComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "PacXmas/GameplayElements/Projectiles/MovementComponent/PXProjectileMovementComponent.h"
#include "PacXmas/GameplayElements/Projectiles/Pudding/PXProjectilePudding.h"
#include "PacXmas/Utilities/CustomLogs/PXCustomLogs.h"

APXPlayer::APXPlayer()
{
	CollisionComponent->SetCollisionProfileName(TEXT("Player"));

	FloatingPawnMovement->MaxSpeed = 400.f;
}

void APXPlayer::BeginPlay()
{
	Super::BeginPlay();
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

		if (Value == 1)
		{
			LastMoveDirection = FVector::ForwardVector;
		}
		else if (Value == -1)
		{
			LastMoveDirection = FVector::BackwardVector;
		}

		Super::MoveHorizontal(Value);
	}
}

void APXPlayer::MoveVertical(const float Value)
{
	if (Value != 0)
	{
		bIsPlayerInputActive = true;

		if (Value == 1)
		{
			LastMoveDirection = FVector::UpVector;
		}
		else if (Value == -1)
		{
			LastMoveDirection = FVector::DownVector;
		}

		Super::MoveVertical(Value);
	}
}

void APXPlayer::ChangeLook()
{
	if (bHasPudding && bHasMusicSheet)
	{
		ActiveDA = PlayerPuddingMusicSheet;
	}
	else if (bHasPudding)
	{
		ActiveDA = PlayerPuddingDA;
	}
	else if (bHasMusicSheet)
	{
		ActiveDA = PlayerMusicSheetDA;
	}
	else
	{
		BackToDefaultFlipbook();
	}
}

void APXPlayer::CollectMusicSheet()
{
	bHasMusicSheet = true;
}

void APXPlayer::CollectPudding()
{
	bHasPudding = true;
}

void APXPlayer::DropMusicSheet()
{
	bHasMusicSheet = false;
}

void APXPlayer::DropPudding()
{
	bHasPudding = false;
}

void APXPlayer::ShootPudding()
{
	constexpr float SpawnDistance{32.f};
	LastMoveDirection.Normalize();
	const FVector SpawnLocation = GetActorLocation() + (LastMoveDirection * SpawnDistance);

	const APXProjectilePudding* SpawnedProjectile = GetWorld()->SpawnActor<APXProjectilePudding>(
		ProjectileClass, SpawnLocation, FRotator::ZeroRotator);

	if (!SpawnedProjectile)
	{
		UE_LOG(LogProjectile, Warning, TEXT("APXPlayer::ShootPudding|SpawnedProjectile is nullptr"))
		return;
	}

	SpawnedProjectile->ChangeSprite(LastMoveDirection);
	SpawnedProjectile->GetMovementComponent()->SetDirection(LastMoveDirection);
}
