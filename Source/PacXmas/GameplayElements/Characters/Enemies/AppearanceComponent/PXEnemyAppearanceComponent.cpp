// Copyright (c) 2023 Santa Claus. All rights reserved.


#include "PXEnemyAppearanceComponent.h"
#include "PaperFlipbookComponent.h"
#include "PacXmas/DataAssets/Characters/Enemies/PXEnemyDA.h"
#include "PacXmas/Utilities/CustomLogs/PXCustomLogs.h"

UPXEnemyAppearanceComponent::UPXEnemyAppearanceComponent()
{
	FlipbookComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Flipbook Component"));
	FlipbookComponent->SetCollisionProfileName(TEXT("NoCollision"));
}

void UPXEnemyAppearanceComponent::BeginPlay()
{
	Super::BeginPlay();

	if (!FlipbookComponent)
	{
		UE_LOG(LogComponent, Warning, TEXT("UPXEnemyAppearanceComponent::BeginPlay|FlipbookComponent is nullptr"))
		return;
	}
	if (!EnemyDA)
	{
		UE_LOG(LogAssetData, Warning, TEXT("UPXPlayerAppearanceComponent::BeginPlay|EnemyDA is nullptr"))
		return;
	}

	FlipbookComponent->SetFlipbook(EnemyDA->IdleFB);
	FlipbookComponent->SetUsingAbsoluteRotation(true);

	FlipbookComponent->OnFinishedPlaying.AddDynamic(this, &UPXEnemyAppearanceComponent::SetFlipbookToEatPudding);
}

void UPXEnemyAppearanceComponent::OnRegister()
{
	Super::OnRegister();

	if (!GetOwner())
	{
		UE_LOG(LogAssetData, Warning, TEXT("UPXEnemyAppearanceComponent::OnRegister|GetOwner() is nullptr"))
		return;
	}

	FlipbookComponent->SetupAttachment(GetOwner()->GetRootComponent());
}

void UPXEnemyAppearanceComponent::SetFlipbookBasedOnActorForwardVector(const FVector& ActorForwardVector) const
{
	if (!FlipbookComponent)
	{
		UE_LOG(LogComponent, Warning,
		       TEXT("UPXEnemyAppearanceComponent::SetFlipbookBasedOnActorForwardVector|FlipbookComponent is nullptr"))
		return;
	}
	if (!EnemyDA)
	{
		UE_LOG(LogAssetData, Warning,
		       TEXT("UPXEnemyAppearanceComponent::SetFlipbookBasedOnActorForwardVector|EnemyDA is nullptr"))
		return;
	}

	if (ActorForwardVector.Equals(FVector::ForwardVector))
	{
		FlipbookComponent->SetFlipbook(EnemyDA->MoveRightFB);
	}
	else if (ActorForwardVector.Equals(FVector::BackwardVector))
	{
		FlipbookComponent->SetFlipbook(EnemyDA->MoveLeftFB);
	}
	else if (ActorForwardVector.Equals(FVector::UpVector))
	{
		FlipbookComponent->SetFlipbook(EnemyDA->MoveUpFB);
	}
	else if (ActorForwardVector.Equals(FVector::DownVector))
	{
		FlipbookComponent->SetFlipbook(EnemyDA->MoveDownFB);
	}
}

void UPXEnemyAppearanceComponent::SetFlipbookGetHitWithPudding(const EEnemyGetHitPudding GetHitPudding) const
{
	if (!FlipbookComponent)
	{
		UE_LOG(LogComponent, Warning,
		       TEXT("UPXEnemyAppearanceComponent::SetFlipbookGetHitWithPudding|FlipbookComponent is nullptr"))
		return;
	}
	if (!EnemyDA)
	{
		UE_LOG(LogAssetData, Warning,
		       TEXT("UPXEnemyAppearanceComponent::SetFlipbookGetHitWithPudding|EnemyDA is nullptr"))
		return;
	}

	switch (GetHitPudding)
	{
	case EEnemyGetHitPudding::Up:
		FlipbookComponent->SetFlipbook(EnemyDA->GetHitPuddingUp);
		break;
	case EEnemyGetHitPudding::Down:
		FlipbookComponent->SetFlipbook(EnemyDA->GetHitPuddingDown);
		break;
	case EEnemyGetHitPudding::Left:
		FlipbookComponent->SetFlipbook(EnemyDA->GetHitPuddingLeft);
		break;
	case EEnemyGetHitPudding::Right:
		FlipbookComponent->SetFlipbook(EnemyDA->GetHitPuddingRight);
		break;
	}
	FlipbookComponent->SetLooping(false);
}

void UPXEnemyAppearanceComponent::SetFlipbookFlashed() const
{
	if (!FlipbookComponent)
	{
		UE_LOG(LogComponent, Warning,
		       TEXT("UPXEnemyAppearanceComponent::SetFlipbookStunned|FlipbookComponent is nullptr"))
		return;
	}
	if (!EnemyDA)
	{
		UE_LOG(LogAssetData, Warning, TEXT("UPXEnemyAppearanceComponent::SetFlipbookStunned|EnemyDA is nullptr"))
		return;
	}

	FlipbookComponent->SetFlipbook(EnemyDA->FlashedFB);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void UPXEnemyAppearanceComponent::SetFlipbookToEatPudding()
{
	if (!FlipbookComponent)
	{
		UE_LOG(LogComponent, Warning,
		       TEXT("UPXEnemyAppearanceComponent::SetFlipbookToEatPudding|FlipbookComponent is nullptr"))
		return;
	}
	if (!EnemyDA)
	{
		UE_LOG(LogAssetData, Warning,
		       TEXT("UPXEnemyAppearanceComponent::SetFlipbookToEatPudding|DevilPuddingDA is nullptr"))
		return;
	}

	FlipbookComponent->SetFlipbook(EnemyDA->EatingPuddingFB);
	FlipbookComponent->SetLooping(true);
	FlipbookComponent->Play();
}
