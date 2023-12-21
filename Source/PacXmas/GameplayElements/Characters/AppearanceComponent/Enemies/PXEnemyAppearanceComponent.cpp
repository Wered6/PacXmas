// Copyright (c) 2023 Santa Claus. All rights reserved.


#include "PXEnemyAppearanceComponent.h"
#include "PaperFlipbookComponent.h"
#include "PacXmas/DataAssets/Characters/Enemies/Devil/PXDevilDA.h"
#include "PacXmas/Utilities/CustomLogs/PXCustomLogs.h"

void UPXEnemyAppearanceComponent::BeginPlay()
{
	Super::BeginPlay();

	if (!FlipbookComponent)
	{
		UE_LOG(LogComponent, Warning, TEXT("UPXEnemyAppearanceComponent::BeginPlay|FlipbookComponent is nullptr"))
		return;
	}

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
	if (!DevilPuddingDA)
	{
		UE_LOG(LogAssetData, Warning,
		       TEXT("UPXEnemyAppearanceComponent::SetFlipbookGetHitWithPudding|DevilPuddingDA is nullptr"))
		return;
	}

	switch (GetHitPudding)
	{
	case EEnemyGetHitPudding::Up:
		FlipbookComponent->SetFlipbook(DevilPuddingDA->GetHitPuddingUpFB);
		break;
	case EEnemyGetHitPudding::Down:
		FlipbookComponent->SetFlipbook(DevilPuddingDA->GetHitPuddingDownFB);
		break;
	case EEnemyGetHitPudding::Left:
		FlipbookComponent->SetFlipbook(DevilPuddingDA->GetHitPuddingLeftFB);
		break;
	case EEnemyGetHitPudding::Right:
		FlipbookComponent->SetFlipbook(DevilPuddingDA->GetHitPuddingRightFB);
		break;
	}
	FlipbookComponent->SetLooping(false);
}

void UPXEnemyAppearanceComponent::SetFlipbookToEatPudding()
{
	if (!FlipbookComponent)
	{
		UE_LOG(LogComponent, Warning,
		       TEXT("UPXEnemyAppearanceComponent::SetFlipbookToEatPudding|FlipbookComponent is nullptr"))
		return;
	}
	if (!DevilPuddingDA)
	{
		UE_LOG(LogAssetData, Warning,
		       TEXT("UPXEnemyAppearanceComponent::SetFlipbookToEatPudding|DevilPuddingDA is nullptr"))
		return;
	}
	
	FlipbookComponent->SetFlipbook(DevilPuddingDA->EatingPuddingFB);
	FlipbookComponent->SetLooping(true);
	FlipbookComponent->Play();
}
