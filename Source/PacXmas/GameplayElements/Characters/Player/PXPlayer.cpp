// Copyright (c) 2023 Smoking Carrots. All rights reserved.


#include "PXPlayer.h"
#include "AppearanceComponent/PXPlayerAppearanceComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "MovementComponent/PXPlayerMovementComponent.h"
#include "PacXmas/GameplayElements/Projectiles/Pudding/PXProjectilePudding.h"
#include "PacXmas/Utilities/CustomLogs/PXCustomLogs.h"

APXPlayer::APXPlayer()
{
	if (!CollisionComponent)
	{
		UE_LOG(LogComponent, Warning, TEXT("APXPlayer::APXPlayer|CollisionComponent is nullptr"))
		return;
	}

	CollisionComponent->SetCollisionProfileName(TEXT("Player"));

	PXPlayerAppearanceComponent = CreateDefaultSubobject<UPXPlayerAppearanceComponent>(TEXT("Appearance Component"));
	PXPlayerMovementComponent = CreateDefaultSubobject<UPXPlayerMovementComponent>(TEXT("Movement Component"));

	PXPlayerAppearanceComponent->InitializeMovementComponent(PXPlayerMovementComponent);

	BindOnShootPuddingAnimationEndDelegate();
}

void APXPlayer::MoveHorizontal(const float Value)
{
	if (!PXPlayerMovementComponent)
	{
		UE_LOG(LogComponent, Warning, TEXT("APXPlayer::MoveHorizontal|PXPlayerMovementComponent is nullptr"))
		return;
	}

	if (Value != 0)
	{
		PXPlayerMovementComponent->SetNextDesiredDirection(FVector(Value, 0.f, 0.f));
	}
}

void APXPlayer::MoveVertical(const float Value)
{
	if (!PXPlayerMovementComponent)
	{
		UE_LOG(LogComponent, Warning, TEXT("APXPlayer::MoveVertical|PXPlayerMovementComponent is nullptr"))
		return;
	}

	if (Value != 0)
	{
		PXPlayerMovementComponent->SetNextDesiredDirection(FVector(0.f, 0.f, Value));
	}
}

void APXPlayer::UpdateDataAsset() const
{
	if (!PXPlayerAppearanceComponent)
	{
		UE_LOG(LogComponent, Warning, TEXT("APXPlayer::ChangeLook|PXPlayerAppearanceComponent is nullptr"))
		return;
	}

	if (bHasPudding && bHasMusicSheet)
	{
		PXPlayerAppearanceComponent->SetCurrentDataAsset(EPlayerLook::PuddingMusicSheet);
	}
	else if (bHasPudding)
	{
		PXPlayerAppearanceComponent->SetCurrentDataAsset(EPlayerLook::Pudding);
	}
	else if (bHasMusicSheet)
	{
		PXPlayerAppearanceComponent->SetCurrentDataAsset(EPlayerLook::MusicSheet);
	}
	else
	{
		PXPlayerAppearanceComponent->SetCurrentDataAsset(EPlayerLook::Default);
	}
}

void APXPlayer::CollectMusicSheet()
{
	bHasMusicSheet = true;
	UpdateDataAsset();
	UpdateFlipbook();
}

void APXPlayer::DropMusicSheet()
{
	bHasMusicSheet = false;
	UpdateDataAsset();
	UpdateFlipbook();
}

bool APXPlayer::GetHasMusicSheet() const
{
	return bHasMusicSheet;
}

void APXPlayer::CollectPudding()
{
	bHasPudding = true;
	UpdateDataAsset();
	UpdateFlipbook();
}

void APXPlayer::ShootPudding()
{
	if (bHasPudding)
	{
		bHasPudding = false;
		UpdateDataAsset();
		UpdateFlipbook();

		PXPlayerMovementComponent->SetCanMove(false);

		OnShootPudding.Broadcast(bHasMusicSheet, GetActorForwardVector());
	}
}

bool APXPlayer::GetHasPudding() const
{
	return bHasPudding;
}

uint8_t APXPlayer::GetLives() const
{
	return Lives;
}

void APXPlayer::LooseLife()
{
	if (!bIsUntouchable)
	{
		if (Lives > 0)
		{
			Lives--;
		}
		if (Lives <= 0)
		{
			HandleGameOver();
		}

		PlayLooseLifeSound();
		UpdateHearts();
		BecomeUntouchable();
		// todo blink when hit
	}
}

// ReSharper disable once CppMemberFunctionMayBeConst
void APXPlayer::ResumeMovement()
{
	PXPlayerMovementComponent->SetCanMove(true);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void APXPlayer::SpawnProjectilePudding()
{
	const FVector ForwardVector = GetActorForwardVector();
	const FVector SpawnLocation = GetActorLocation();
	const FRotator ProjectileRotation = ForwardVector.Rotation();

	GetWorld()->SpawnActor<APXProjectilePudding>(ProjectileClass, SpawnLocation, ProjectileRotation);
	// todo add sound
}

void APXPlayer::PlayLooseLifeSound() const
{
	if (!LooseLifeSound)
	{
		UE_LOG(LogSound, Warning, TEXT("APXPlayer::PlayLooseLifeSound|LooseLifeSound is nullptr"))
		return;
	}

	UGameplayStatics::PlaySoundAtLocation(this, LooseLifeSound, GetActorLocation());
}

void APXPlayer::UpdateFlipbook() const
{
	if (!PXPlayerAppearanceComponent)
	{
		UE_LOG(LogComponent, Warning, TEXT("APXPlayer::UpdateFlipbook|PXPlayerAppearanceComponent is nullptr"))
		return;
	}

	PXPlayerAppearanceComponent->UpdateFlipbookToForwardVector();
}

void APXPlayer::BindOnShootPuddingAnimationEndDelegate()
{
	if (!PXPlayerAppearanceComponent)
	{
		UE_LOG(LogComponent, Warning,
		       TEXT("APXPlayer::BindOnShootPuddingAnimationEndDelegate|PXPlayerAppearanceComponent is nullptr"))
		return;
	}

	PXPlayerAppearanceComponent->OnShootPuddingAnimationEnd.AddDynamic(this, &APXPlayer::SpawnProjectilePudding);
	PXPlayerAppearanceComponent->OnShootPuddingAnimationEnd.AddDynamic(this, &APXPlayer::ResumeMovement);
}

void APXPlayer::HandleGameOver() const
{
	if (!PXPlayerAppearanceComponent)
	{
		UE_LOG(LogComponent, Warning, TEXT("APXPlayer::GameOver|PXPlayerAppearanceComponent is nullptr"))
		return;
	}
	if (!PXPlayerMovementComponent)
	{
		UE_LOG(LogComponent, Warning, TEXT("APXPlayer::GameOver|PXPlayerMovementComponent is nullptr"))
		return;
	}

	PXPlayerAppearanceComponent->SetFlipbookToGameOver();
	PXPlayerMovementComponent->SetCanMove(false);

	// todo when shooting pudding in the same time it not work

	OnGameOver.Broadcast();
	// todo give some sign "You died or something"
}

void APXPlayer::UpdateHearts() const
{
	OnPlayerHUDUpdate.Broadcast();
}

void APXPlayer::BecomeUntouchable()
{
	bIsUntouchable = true;

	GetWorld()->GetTimerManager().SetTimer(UntouchableTimerHandle, this, &APXPlayer::BecomeTouchable,
	                                       UntouchableDuration);
}

void APXPlayer::BecomeTouchable()
{
	bIsUntouchable = false;
}
