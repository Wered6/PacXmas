// Copyright (c) 2023 Smoking Carrots. All rights reserved.


#include "PXEnemyAppearanceComponent.h"
#include "PaperFlipbookComponent.h"
#include "PacXmas/DataAssets/Characters/Enemies/PXEnemyDA.h"
#include "PacXmas/Utilities/CustomLogs/PXCustomLogs.h"

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

	// Set DA for polymorphism
	PXCharacterDA = EnemyDA;

	FlipbookComponent->SetFlipbook(PXCharacterDA->GetIdleFB());

	FlipbookComponent->OnFinishedPlaying.AddDynamic(this, &UPXEnemyAppearanceComponent::SetFlipbookToEatPudding);
}

void UPXEnemyAppearanceComponent::SetFlipbookGetHitWithPudding(const EEnemyGetHitPudding GetHitPudding) const
{
	if (!FlipbookComponent)
	{
		UE_LOG(LogComponent, Warning,
		       TEXT("UPXEnemyAppearanceComponent::SetFlipbookGetHitWithPudding|FlipbookComponent is nullptr"))
		return;
	}
	if (!PXCharacterDA)
	{
		UE_LOG(LogAssetData, Warning,
		       TEXT("UPXEnemyAppearanceComponent::SetFlipbookGetHitWithPudding|EnemyDA is nullptr"))
		return;
	}

	switch (GetHitPudding)
	{
	case EEnemyGetHitPudding::Up:
		FlipbookComponent->SetFlipbook(PXCharacterDA->GetHitPuddingUpFB());
		break;
	case EEnemyGetHitPudding::Down:
		FlipbookComponent->SetFlipbook(PXCharacterDA->GetHitPuddingDownFB());
		break;
	case EEnemyGetHitPudding::Left:
		FlipbookComponent->SetFlipbook(PXCharacterDA->GetHitPuddingLeftFB());
		break;
	case EEnemyGetHitPudding::Right:
		FlipbookComponent->SetFlipbook(PXCharacterDA->GetHitPuddingRightFB());
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
	if (!PXCharacterDA)
	{
		UE_LOG(LogAssetData, Warning, TEXT("UPXEnemyAppearanceComponent::SetFlipbookStunned|EnemyDA is nullptr"))
		return;
	}

	FlipbookComponent->SetFlipbook(PXCharacterDA->GetFlashedFB());
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
	if (!PXCharacterDA)
	{
		UE_LOG(LogAssetData, Warning,
		       TEXT("UPXEnemyAppearanceComponent::SetFlipbookToEatPudding|DevilPuddingDA is nullptr"))
		return;
	}

	FlipbookComponent->SetFlipbook(PXCharacterDA->GetEatingPuddingFB());
	FlipbookComponent->SetLooping(true);
	FlipbookComponent->Play();
}
