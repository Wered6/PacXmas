// Copyright (c) 2023 Smoking Carrots. All rights reserved.


#include "PXEnemy.h"
#include "AppearanceComponent/PXEnemyAppearanceComponent.h"
#include "Components/BoxComponent.h"
#include "MovementComponent/PXEnemyMovementComponent.h"
#include "PacXmas/GameplayElements/Characters/Player/PXPlayer.h"
#include "PacXmas/Utilities/CustomLogs/PXCustomLogs.h"

APXEnemy::APXEnemy()
{
	if (!CollisionComponent)
	{
		UE_LOG(LogComponent, Warning, TEXT("APXEnemy::APXEnemy|CollisioComponent is nullptr"))
		return;
	}

	CollisionComponent->SetCollisionProfileName(TEXT("Enemy"));
	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &APXEnemy::OnOverlapBegin);

	PXEnemyMovementComponent = CreateDefaultSubobject<UPXEnemyMovementComponent>(TEXT("Movement Component"));
	PXEnemyAppearanceComponent = CreateDefaultSubobject<UPXEnemyAppearanceComponent>(TEXT("Appearance Component"));

	PXEnemyAppearanceComponent->InitializeMovementComponent(PXEnemyMovementComponent);
}

void APXEnemy::EatPudding()
{
	StunYourself(EatingPuddingTime);

	const FVector ActorForwardVector = GetActorForwardVector();

	if (!PXEnemyAppearanceComponent)
	{
		UE_LOG(LogComponent, Warning, TEXT("APXEnemy::EatPudding|PXEnemyAppearanceComponent is nullptr"))
		return;
	}
	if (!PXEnemyMovementComponent)
	{
		UE_LOG(LogComponent, Warning, TEXT("APXEnemy::EatPudding|PXEnemyMovementComponent is nullptr"))
		return;
	}

	const bool bCanMove = PXEnemyMovementComponent->GetCanMove();

	if (ActorForwardVector.Equals(FVector::DownVector) || bCanMove)
	{
		PXEnemyAppearanceComponent->SetFlipbookGetHitWithPudding(EEnemyGetHitPudding::Down);
	}
	else if (ActorForwardVector.Equals(FVector::ForwardVector))
	{
		PXEnemyAppearanceComponent->SetFlipbookGetHitWithPudding(EEnemyGetHitPudding::Right);
	}
	else if (ActorForwardVector.Equals(FVector::BackwardVector))
	{
		PXEnemyAppearanceComponent->SetFlipbookGetHitWithPudding(EEnemyGetHitPudding::Left);
	}
	else if (ActorForwardVector.Equals(FVector::UpVector))
	{
		PXEnemyAppearanceComponent->SetFlipbookGetHitWithPudding(EEnemyGetHitPudding::Up);
	}
}

void APXEnemy::GetFlashed()
{
	StunYourself(FlashedTime);

	if (!PXEnemyAppearanceComponent)
	{
		UE_LOG(LogComponent, Warning, TEXT("APXEnemy::GetFlashed|PXEnemyAppearanceComponent is nullptr"))
		return;
	}

	PXEnemyAppearanceComponent->SetFlipbookFlashed();
}

void APXEnemy::SetCanMove(const bool bCanMove) const
{
	if (!PXEnemyMovementComponent)
	{
		UE_LOG(LogComponent, Warning, TEXT("APXEnemy::SetCanMove|PXEnemyMovementComponent is nullptr"))
		return;
	}

	PXEnemyMovementComponent->SetCanMove(bCanMove);
}

void APXEnemy::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                              UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep,
                              const FHitResult& SweepResult)
{
	if (!PXEnemyMovementComponent)
	{
		UE_LOG(LogComponent, Warning, TEXT("APXEnemy::OnOverlapBegin|PXEnemyMovementComponent is nullptr"))
		return;
	}

	APXPlayer* PXPlayer = Cast<APXPlayer>(OtherActor);
	const bool bCanMove = PXEnemyMovementComponent->GetCanMove();

	if (PXPlayer && bCanMove)
	{
		PXPlayer->LooseLife();
	}
}

void APXEnemy::StunYourself(const float Time)
{
	if (!PXEnemyMovementComponent)
	{
		UE_LOG(LogComponent, Warning, TEXT("APXEnemy::StunYourself|PXEnemyMovementComponent is nullptr"))
		return;
	}

	PXEnemyMovementComponent->SetCanMove(false);

	// Check if the timer is already active and reset/extend it
	if (GetWorld()->GetTimerManager().IsTimerActive(StunTimerHandle))
	{
		GetWorld()->GetTimerManager().ClearTimer(StunTimerHandle);
	}

	GetWorld()->GetTimerManager().SetTimer(StunTimerHandle, this, &APXEnemy::ResumeMovement, Time);
}

void APXEnemy::ResumeMovement() const
{
	if (!PXEnemyMovementComponent)
	{
		UE_LOG(LogComponent, Warning, TEXT("APXEnemy::ResetStun|PXEnemyMovementComponent is nullptr"))
		return;
	}

	PXEnemyMovementComponent->SetCanMove(true);
}
