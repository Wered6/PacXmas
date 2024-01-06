// Copyright (c) 2023 Smoking Carrots. All rights reserved.


#include "PXEnemy.h"
#include "AppearanceComponent/PXEnemyAppearanceComponent.h"
#include "Components/BoxComponent.h"
#include "PacXmas/GameplayElements/Characters/MovementComponent/PXCharacterMovementComponent.h"
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

	if (!PXCharacterMovementComponent)
	{
		UE_LOG(LogComponent, Warning, TEXT("APXEnemy::APXEnemy|PXCharacterMovementComponent is nullptr"))
		return;
	}

	PXCharacterMovementComponent->SetIsAIControlled(true);
	PXCharacterMovementComponent->SetCanAIMove(true);

	PXEnemyAppearanceComponent = CreateDefaultSubobject<UPXEnemyAppearanceComponent>(TEXT("Appearance Component"));
}

void APXEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!PXEnemyAppearanceComponent)
	{
		UE_LOG(LogComponent, Warning, TEXT("APXEnemy::Tick|PXEnemeyApperanceComponent is nullptr"))
		return;
	}
	if (!PXCharacterMovementComponent)
	{
		UE_LOG(LogComponent, Warning, TEXT("APXEnemy::Tick|PXCharacterMovementComponent is nullptr"))
		return;
	}

	const bool bCanAIMove = PXCharacterMovementComponent->GetCanAIMove();

	if (bCanAIMove)
	{
		const FVector ForwardVector = GetActorForwardVector();
		PXEnemyAppearanceComponent->SetFlipbookBasedOnActorForwardVector(ForwardVector);
	}
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
	if (!PXCharacterMovementComponent)
	{
		UE_LOG(LogComponent, Warning, TEXT("APXEnemy::EatPudding|PXCharacterMovementComponent is nullptr"))
		return;
	}

	const bool bCanAIMove = PXCharacterMovementComponent->GetCanAIMove();

	if (ActorForwardVector.Equals(FVector::DownVector) || bCanAIMove)
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

void APXEnemy::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                              UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep,
                              const FHitResult& SweepResult)
{
	if (!PXCharacterMovementComponent)
	{
		UE_LOG(LogComponent, Warning, TEXT("APXEnemy::OnOverlapBegin|PXCharacterMovementComponent is nullptr"))
		return;
	}

	APXPlayer* PXPlayer = Cast<APXPlayer>(OtherActor);
	const bool bCanAIMove = PXCharacterMovementComponent->GetCanAIMove();

	if (PXPlayer && bCanAIMove)
	{
		PXPlayer->LooseLife();
	}
}

void APXEnemy::StunYourself(const float Time)
{
	if (!PXCharacterMovementComponent)
	{
		UE_LOG(LogComponent, Warning, TEXT("APXEnemy::StunYourself|PXCharacterMovementComponent is nullptr"))
		return;
	}

	PXCharacterMovementComponent->SetCanAIMove(false);

	// Check if the timer is already active and reset/extend it
	if (GetWorld()->GetTimerManager().IsTimerActive(StunTimerHandle))
	{
		GetWorld()->GetTimerManager().ClearTimer(StunTimerHandle);
	}

	GetWorld()->GetTimerManager().SetTimer(StunTimerHandle, this, &APXEnemy::ResetStun, Time);
}

void APXEnemy::ResetStun() const
{
	if (!PXCharacterMovementComponent)
	{
		UE_LOG(LogComponent, Warning, TEXT("APXEnemy::ResetStun|PXCharacterMovementComponent is nullptr"))
		return;
	}

	PXCharacterMovementComponent->SetCanAIMove(true);
}
