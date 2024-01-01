// Copyright (c) 2023 Santa Claus. All rights reserved.


#include "PXPlayer.h"
#include "AppearanceComponent/PXPlayerAppearanceComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PacXmas/GameplayElements/Characters/MovementComponent/PXCharacterMovementComponent.h"
#include "PacXmas/GameplayElements/Projectiles/Pudding/PXProjectilePudding.h"
#include "PacXmas/PlayerControllers/Gameplay/PXPlayerControllerGameplay.h"
#include "PacXmas/UI/HUD/PXHUD.h"
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
}

void APXPlayer::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (!PXPlayerAppearanceComponent)
	{
		UE_LOG(LogComponent, Warning, TEXT("APXPlayer::MoveHorizontal|PXPlayerAppearanceComponent is nullptr"))
		return;
	}
	if (!PXCharacterMovementComponent)
	{
		UE_LOG(LogComponent, Warning, TEXT("APXPlayer::Tick|PXPlayerMovementComponent is nullptr"))
		return;
	}

	const bool bIsMoving = PXCharacterMovementComponent->GetIsMoving();

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

void APXPlayer::MoveHorizontal(const float Value)
{
	if (Value != 0)
	{
		PXCharacterMovementComponent->SetDesiredDirection(FVector(Value, 0.f, 0.f));
	}
}

void APXPlayer::MoveVertical(const float Value)
{
	if (Value != 0)
	{
		PXCharacterMovementComponent->SetDesiredDirection(FVector(0.f, 0.f, Value));
	}
}

void APXPlayer::ResetMovementComponent() const
{
	if (!PXCharacterMovementComponent)
	{
		UE_LOG(LogComponent, Warning, TEXT("APXPlayer::ResetMovementComponent|PXCharacterMovementComponent is nullptr"))
		return;
	}

	PXCharacterMovementComponent->ResetTargetLocation();
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
		UGameplayStatics::OpenLevel(this, FName("Menu"));
	}
}

void APXPlayer::HeartBlinking() const
{
	const APXPlayerControllerGameplay* PlayerController = Cast<APXPlayerControllerGameplay>(GetController());

	if (!PlayerController)
	{
		UE_LOG(LogController, Warning, TEXT("APXPlayer::HeartBlinking|PlayerController is nullptr"))
		return;
	}

	APXHUD* PXHUD = Cast<APXHUD>(PlayerController->GetHUD());

	if (!PXHUD)
	{
		UE_LOG(LogHUD, Warning, TEXT("APXPlayer::HeartBlinking|PXHUD is nullptr"))
		return;
	}

	PXHUD->StartHeartBlinking();
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

void APXPlayer::SpawnProjectilePudding() const
{
	const FVector ForwardVector = GetActorForwardVector();
	const FVector SpawnLocation = GetActorLocation();
	const FRotator ProjectileRotation = ForwardVector.Rotation();

	GetWorld()->SpawnActor<APXProjectilePudding>(ProjectileClass, SpawnLocation, ProjectileRotation);
}
