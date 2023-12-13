// Copyright (c) 2023 Santa Claus. All rights reserved.


#include "PXPlayer.h"
#include "Components/BoxComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "PacXmas/GameplayElements/Projectiles/Pudding/PXProjectilePudding.h"
#include "PacXmas/PlayerControllers/Gameplay/PXPlayerControllerGameplay.h"
#include "PacXmas/UI/HUD/PXHUD.h"
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
	if (bHasPudding)
	{
		SpawnPudding();
		ChangeLook();
	}
}

uint8_t APXPlayer::GetLives() const
{
	return Lives;
}

void APXPlayer::LoseLive()
{
	if (!bIsInvincible)
	{
		if (Lives > 0)
		{
			Lives--;
		}

		const APXPlayerControllerGameplay* PlayerController = Cast<APXPlayerControllerGameplay>(GetController());

		if (!PlayerController)
		{
			UE_LOG(LogController, Warning, TEXT("APXPlayer::LoseLive|PlayerController is nullptr"))
			return;
		}

		APXHUD* PXHUD = Cast<APXHUD>(PlayerController->GetHUD());

		if (!PXHUD)
		{
			UE_LOG(LogHUD, Warning, TEXT("APXPlayer::LoseLive|PXHUD is nullptr"))
			return;
		}

		PXHUD->StartHeartBlinking();

		constexpr float InvincibleDuration{1.2f};
		bIsInvincible = true;
		GetWorld()->GetTimerManager().SetTimer(InvincibleTimerHandle, [this]()
		{
			bIsInvincible = false;
		}, InvincibleDuration, false);
	}
}

void APXPlayer::SpawnPudding()
{
	constexpr float SpawnDistance{32.f};
	const FVector ProjectileDirection = LastMoveDirection.GetSafeNormal();
	const FVector SpawnLocation = GetActorLocation() + (ProjectileDirection * SpawnDistance);

	APXProjectilePudding* ProjectilePudding = GetWorld()->SpawnActor<APXProjectilePudding>(
		ProjectileClass, SpawnLocation, FRotator::ZeroRotator);

	if (!ProjectilePudding)
	{
		UE_LOG(LogActor, Warning, TEXT("APXPlayer::ShootPudding|ProjectilePudding is nullptr"))
		return;
	}

	ProjectilePudding->SetActorRotationBasedOnLastMoveDirection(ProjectileDirection);

	bHasPudding = false;
}
