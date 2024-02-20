// Copyright (c) 2023 Smoking Carrots. All rights reserved.


#include "PXPlayerAppearanceComponent.h"
#include "PaperFlipbookComponent.h"
#include "PacXmas/DataAssets/Characters/Player/PXPlayerDA.h"
#include "PacXmas/DataAssets/Characters/Player/PXPlayerThrowPuddingDA.h"
#include "PacXmas/GameplayElements/Characters/Player/PXPlayer.h"
#include "PacXmas/Utilities/CustomLogs/PXCustomLogs.h"

void UPXPlayerAppearanceComponent::BeginPlay()
{
	Super::BeginPlay();

	if (!FlipbookComponent)
	{
		UE_LOG(LogComponent, Warning, TEXT("UPXPlayerAppearanceComponent::BeginPlay|FlipbookComponent is nullptr"))
		return;
	}
	if (!PXPlayerDefaultDA)
	{
		UE_LOG(LogAssetData, Warning, TEXT("UPXPlayerAppearanceComponent::BeginPlay|PlayerDefaultDA is nullptr"))
		return;
	}

	// Set DA for polymorphism
	PXCharacterDA = PXPlayerDefaultDA;

	FlipbookComponent->SetFlipbook(PXCharacterDA->GetIdleFB());

	FlipbookComponent->OnFinishedPlaying.AddDynamic(this, &UPXPlayerAppearanceComponent::ThrowPuddingAnimationFinished);

	APXPlayer* PXPlayer = Cast<APXPlayer>(GetOwner());
	PXPlayer->OnShootPudding.AddDynamic(this, &UPXPlayerAppearanceComponent::PlayThrowPuddingAnimation);
}

void UPXPlayerAppearanceComponent::SetCurrentDataAsset(const EPlayerLook PlayerLook)
{
	if (!PXCharacterDA)
	{
		UE_LOG(LogAssetData, Warning, TEXT("UPXPlayerAppearanceComponent::SetDataAsset|PlayerCurrentDA is nullptr"))
		return;
	}
	if (!PXPlayerDefaultDA)
	{
		UE_LOG(LogAssetData, Warning, TEXT("UPXPlayerAppearanceComponent::SetDataAsset|PlayerDefaultDA is nullptr"))
		return;
	}
	if (!PXPlayerPuddingDA)
	{
		UE_LOG(LogAssetData, Warning, TEXT("UPXPlayerAppearanceComponent::SetDataAsset|PlayerPuddingDA is nullptr"))
		return;
	}
	if (!PXPlayerMusicSheetDA)
	{
		UE_LOG(LogAssetData, Warning, TEXT("UPXPlayerAppearanceComponent::SetDataAsset|PlayerMusicSheetDA is nullptr"))
		return;
	}
	if (!PXPlayerPuddingMusicSheet)
	{
		UE_LOG(LogAssetData, Warning,
		       TEXT("UPXPlayerAppearanceComponent::SetDataAsset|PlayerPuddingMusicSheetDA is nullptr"))
		return;
	}

	switch (PlayerLook)
	{
	case EPlayerLook::Default:
		PXCharacterDA = PXPlayerDefaultDA;
		break;
	case EPlayerLook::Pudding:
		PXCharacterDA = PXPlayerPuddingDA;
		break;
	case EPlayerLook::MusicSheet:
		PXCharacterDA = PXPlayerMusicSheetDA;
		break;
	case EPlayerLook::PuddingMusicSheet:
		PXCharacterDA = PXPlayerPuddingMusicSheet;
		break;
	default:
		break;
	}
}

void UPXPlayerAppearanceComponent::SetFlipbookIdle() const
{
	if (!FlipbookComponent)
	{
		UE_LOG(LogComponent, Warning,
		       TEXT("UPXPlayerAppearanceComponent::SetFlipbookIdle|FlipbookComponent is nullptr"))
		return;
	}
	if (!PXCharacterDA)
	{
		UE_LOG(LogAssetData, Warning, TEXT("UPXPlayerAppearanceComponent::SetFlipbookIdle|PlayerCurrentDA is nullptr"))
		return;
	}

	FlipbookComponent->SetFlipbook(PXCharacterDA->GetIdleFB());
}

// ReSharper disable once CppMemberFunctionMayBeConst
void UPXPlayerAppearanceComponent::SetFlipbookToGameOver()
{
	if (!FlipbookComponent)
	{
		UE_LOG(LogComponent, Warning,
		       TEXT("UPXPlayerAppearanceComponent::SetFlipbookToGameOver|FlipbookComponent is nullptr"))
		return;
	}
	if (!PXCharacterDA)
	{
		UE_LOG(LogAssetData, Warning,
		       TEXT("UPXPlayerAppearanceComponent::SetFlipbookToGameOver|PlayerCurrentDA is nullptr"))
		return;
	}

	FlipbookComponent->SetFlipbook(PXCharacterDA->GetGameOverFB());
}

// ReSharper disable once CppPassValueParameterByConstReference
// ReSharper disable once CppParameterMayBeConst
void UPXPlayerAppearanceComponent::PlayThrowPuddingAnimation(bool bHasMusicSheet, FVector ActorForwardVector)
{
	if (!FlipbookComponent)
	{
		UE_LOG(LogComponent, Warning,
		       TEXT("UPXPlayerAppearanceComponent::PlayThrowPuddingAnimation|FlipbookComponent is nullptr"))
		return;
	}

	const UPXPlayerThrowPuddingDA* PXPlayerCurrentThrowPuddingDA = ChoosePXPlayerThrowPuddingDA(bHasMusicSheet);

	if (!PXPlayerCurrentThrowPuddingDA)
	{
		UE_LOG(LogAssetData, Warning,
		       TEXT("UPXPlayerAppearanceComponent::PlayThrowPuddingAnimation|PXPlayerCurrnetThrowPuddingDA is nullptr"))
		return;
	}

	if (ActorForwardVector.Equals(FVector::ForwardVector))
	{
		FlipbookComponent->SetFlipbook(PXPlayerCurrentThrowPuddingDA->ThrowPuddingRight);
	}
	else if (ActorForwardVector.Equals(FVector::BackwardVector))
	{
		FlipbookComponent->SetFlipbook(PXPlayerCurrentThrowPuddingDA->ThrowPuddingLeft);
	}
	else if (ActorForwardVector.Equals(FVector::UpVector))
	{
		FlipbookComponent->SetFlipbook(PXPlayerCurrentThrowPuddingDA->ThrowPuddingUp);
	}
	else if (ActorForwardVector.Equals(FVector::DownVector))
	{
		FlipbookComponent->SetFlipbook(PXPlayerCurrentThrowPuddingDA->ThrowPuddingDown);
	}

	FlipbookComponent->SetLooping(false);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void UPXPlayerAppearanceComponent::ThrowPuddingAnimationFinished()
{
	if (!FlipbookComponent)
	{
		UE_LOG(LogComponent, Warning,
		       TEXT("UPXPlayerAppearanceComponent::SetFlipbookToLoop|FlipbookComponent is nullptr"))
		return;
	}

	SetFlipbookIdle();

	FlipbookComponent->SetLooping(true);
	FlipbookComponent->Play();

	OnShootPuddingAnimationEnd.Broadcast();
}

// ReSharper disable once CppMemberFunctionMayBeConst
UPXPlayerThrowPuddingDA* UPXPlayerAppearanceComponent::ChoosePXPlayerThrowPuddingDA(const bool bHasMusicSheet)
{
	if (!PXPlayerPuddingThrowPuddingDA)
	{
		UE_LOG(LogAssetData, Warning,
		       TEXT(
			       "UPXPlayerAppearanceComponent::ChoosePXPlayerThrowPuddingDA|PXPlayerPuddingThrowPuddingDA is nullptr"
		       ))
		return nullptr;
	}
	if (!PXPlayerPuddingMusicSheetThrowPuddingDA)
	{
		UE_LOG(LogAssetData, Warning,
		       TEXT(
			       "UPXPlayerAppearanceComponent::ChoosePXPlayerThrowPuddingDA|PXPlayerPuddingMusicSheetThrowPuddingDA is nullptr"
		       ))
		return nullptr;
	}

	if (bHasMusicSheet)
	{
		return PXPlayerPuddingMusicSheetThrowPuddingDA;
	}
	return PXPlayerPuddingThrowPuddingDA;
}
