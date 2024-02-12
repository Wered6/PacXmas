// Copyright (c) 2023 Smoking Carrots. All rights reserved.


#include "PXPlayer.h"
#include "AppearanceComponent/PXPlayerAppearanceComponent.h"
#include "Components/BoxComponent.h"
#include "MovementComponent/PXPlayerMovementComponent.h"
#include "PacXmas/GameplayElements/Projectiles/Pudding/PXProjectilePudding.h"
#include "PacXmas/Utilities/CustomLogs/PXCustomLogs.h"

APXPlayer::APXPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	if (!CollisionComponent)
	{
		UE_LOG(LogComponent, Warning, TEXT("APXPlayer::APXPlayer|CollisionComponent is nullptr"))
		return;
	}

	CollisionComponent->SetCollisionProfileName(TEXT("Player"));

	PXPlayerAppearanceComponent = CreateDefaultSubobject<UPXPlayerAppearanceComponent>(TEXT("Appearance Component"));
	PXPlayerMovementComponent = CreateDefaultSubobject<UPXPlayerMovementComponent>(TEXT("Movement Component"));
}

void APXPlayer::BeginPlay()
{
	Super::BeginPlay();

	if (!PXPlayerAppearanceComponent)
	{
		UE_LOG(LogComponent, Warning, TEXT("APXPlayer::BeginPlay|PXPlayerAppearanceComponent is nullptr"))
		return;
	}
	
	PXPlayerAppearanceComponent->OnShootPuddingAnimationEnd.AddDynamic(this, &APXPlayer::SpawnProjectilePudding);
	PXPlayerAppearanceComponent->OnShootPuddingAnimationEnd.AddDynamic(this, &APXPlayer::ResumeMovement);
}

void APXPlayer::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (!PXPlayerAppearanceComponent)
	{
		UE_LOG(LogComponent, Warning, TEXT("APXPlayer::MoveHorizontal|PXPlayerAppearanceComponent is nullptr"))
		return;
	}
	if (!PXPlayerMovementComponent)
	{
		UE_LOG(LogComponent, Warning, TEXT("APXPlayer::Tick|PXPlayerMovementComponent is nullptr"))
		return;
	}

	const bool bIsMoving = PXPlayerMovementComponent->GetIsMoving();
	const bool bCanMove = PXPlayerMovementComponent->GetCanMove();

	if (bCanMove)
	{
		if (!bIsMoving)
		{
			PXPlayerAppearanceComponent->SetFlipbookIdle();
		}
		else
		{
			const FVector ForwardVector = GetActorForwardVector();
			PXPlayerAppearanceComponent->SetFlipbookBasedOnActorForwardVector(ForwardVector);
		}
	}
}

void APXPlayer::MoveHorizontal(const float Value)
{
	if (Value != 0)
	{
		PXPlayerMovementComponent->SetNextDesiredDirection(FVector(Value, 0.f, 0.f));
	}
}

void APXPlayer::MoveVertical(const float Value)
{
	if (Value != 0)
	{
		PXPlayerMovementComponent->SetNextDesiredDirection(FVector(0.f, 0.f, Value));
	}
}

void APXPlayer::ChangeLook() const
{
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
	ChangeLook();
}

void APXPlayer::DropMusicSheet()
{
	bHasMusicSheet = false;
	ChangeLook();
}

bool APXPlayer::GetHasMusicSheet() const
{
	return bHasMusicSheet;
}

void APXPlayer::CollectPudding()
{
	bHasPudding = true;
	ChangeLook();
}

void APXPlayer::ShootPudding()
{
	if (bHasPudding)
	{
		bHasPudding = false;
		ChangeLook();

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

		HeartBlinking();
		BecomeUntouchable();
	}

	if (Lives <= 0)
	{
		HandleGameOver();
	}
}

// ReSharper disable once CppMemberFunctionMayBeConst
void APXPlayer::ResumeMovement()
{
	PXPlayerMovementComponent->SetCanMove(true);
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

	OnGameOver.Broadcast();
}

void APXPlayer::HeartBlinking() const
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

// ReSharper disable once CppMemberFunctionMayBeConst
void APXPlayer::SpawnProjectilePudding()
{
	const FVector ForwardVector = GetActorForwardVector();
	const FVector SpawnLocation = GetActorLocation();
	const FRotator ProjectileRotation = ForwardVector.Rotation();

	GetWorld()->SpawnActor<APXProjectilePudding>(ProjectileClass, SpawnLocation, ProjectileRotation);
}
