// Copyright (c) 2023 Santa Claus. All rights reserved.


#include "PXPlayer.h"
#include "Components/BoxComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "PacXmas/GameplayElements/Characters/AppearanceComponent/Player/PXPlayerAppearanceComponent.h"
#include "PacXmas/GameplayElements/Projectiles/Pudding/PXProjectilePudding.h"
#include "PacXmas/PlayerControllers/Gameplay/PXPlayerControllerGameplay.h"
#include "PacXmas/UI/HUD/PXHUD.h"
#include "PacXmas/Utilities/CustomLogs/PXCustomLogs.h"

APXPlayer::APXPlayer()
{
	CollisionComponent->SetCollisionProfileName(TEXT("Player"));

	if (!FloatingPawnMovement)
	{
		UE_LOG(LogComponent, Warning, TEXT("APXPlayer::APXPlayer|FloatingPawnMovement is nullptr"))
		return;
	}

	FloatingPawnMovement->MaxSpeed = 400.f;

	PlayerAppearanceComponent = CreateDefaultSubobject<UPXPlayerAppearanceComponent>(TEXT("Appearance Component"));
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
		PlayerAppearanceComponent->SetFlipbookBasedOnDirection(ECharacterDirection::Idle);
	}

	bIsPlayerInputActive = false;
}

void APXPlayer::MoveHorizontal(const float Value)
{
	if (Value != 0)
	{
		Super::MoveHorizontal(Value);

		bIsPlayerInputActive = true;

		const int8 Sign = FMath::Sign(Value);

		switch (Sign)
		{
		case 1:
			LastMoveDirection = FVector::ForwardVector;
			break;
		case -1:
			LastMoveDirection = FVector::BackwardVector;
			break;
		}

		if (!PlayerAppearanceComponent)
		{
			UE_LOG(LogComponent, Warning, TEXT("APXPlayer::MoveHorizontal|PlayerAppearanceComponent is nullptr"))
			return;
		}

		PlayerAppearanceComponent->SetFlipbookBasedOnAxis(Sign, EAxisMovement::Horizontal);
	}
}

void APXPlayer::MoveVertical(const float Value)
{
	if (Value != 0)
	{
		Super::MoveVertical(Value);

		bIsPlayerInputActive = true;

		const int8 Sign = FMath::Sign(Value);

		switch (Sign)
		{
		case 1:
			LastMoveDirection = FVector::UpVector;
			break;
		case -1:
			LastMoveDirection = FVector::DownVector;
			break;
		}

		if (!PlayerAppearanceComponent)
		{
			UE_LOG(LogComponent, Warning, TEXT("APXPlayer::MoveVertical|PlayerAppearanceComponent is nullptr"))
			return;
		}

		PlayerAppearanceComponent->SetFlipbookBasedOnAxis(Sign, EAxisMovement::Vertical);
	}
}

void APXPlayer::ChangeLook() const
{
	if (bHasPudding && bHasMusicSheet)
	{
		PlayerAppearanceComponent->SetDataAsset(EPlayerLook::PuddingMusicSheet);
	}
	else if (bHasPudding)
	{
		PlayerAppearanceComponent->SetDataAsset(EPlayerLook::Pudding);
	}
	else if (bHasMusicSheet)
	{
		PlayerAppearanceComponent->SetDataAsset(EPlayerLook::MusicSheet);
	}
	else
	{
		PlayerAppearanceComponent->SetDataAsset(EPlayerLook::Default);
	}
}

void APXPlayer::CollectMusicSheet()
{
	bHasMusicSheet = true;
	MusicSheetCount++;
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

uint8_t APXPlayer::GetMusicSheetCount() const
{
	return MusicSheetCount;
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
		SpawnProjectilePudding();
		ChangeLook();
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

void APXPlayer::SpawnProjectilePudding()
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
