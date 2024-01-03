// Copyright (c) 2023 Santa Claus. All rights reserved.


#include "PXPlayerAppearanceComponent.h"
#include "PaperFlipbookComponent.h"
#include "PacXmas/DataAssets/Characters/Player/PXPlayerDA.h"
#include "PacXmas/Utilities/CustomLogs/PXCustomLogs.h"

UPXPlayerAppearanceComponent::UPXPlayerAppearanceComponent()
{
	FlipbookComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Flipbook Component"));
	FlipbookComponent->SetCollisionProfileName(TEXT("NoCollision"));
}

void UPXPlayerAppearanceComponent::BeginPlay()
{
	Super::BeginPlay();

	if (!FlipbookComponent)
	{
		UE_LOG(LogComponent, Warning, TEXT("UPXPlayerAppearanceComponent::BeginPlay|FlipbookComponent is nullptr"))
		return;
	}
	if (!PlayerDefaultDA)
	{
		UE_LOG(LogAssetData, Warning, TEXT("UPXPlayerAppearanceComponent::BeginPlay|PlayerDefaultDA is nullptr"))
		return;
	}

	PlayerCurrentDA = PlayerDefaultDA;

	FlipbookComponent->SetFlipbook(PlayerCurrentDA->IdleFB);
	FlipbookComponent->SetUsingAbsoluteRotation(true);
}

void UPXPlayerAppearanceComponent::OnRegister()
{
	Super::OnRegister();

	if (!GetOwner())
	{
		UE_LOG(LogActor, Warning, TEXT("UPXPlayerAppearanceComponent::OnRegister|GetOwner() is nullptr"))
		return;
	}

	FlipbookComponent->SetupAttachment(GetOwner()->GetRootComponent());
}

void UPXPlayerAppearanceComponent::SetCurrentDataAsset(const EPlayerLook PlayerLook)
{
	if (!PlayerCurrentDA)
	{
		UE_LOG(LogAssetData, Warning, TEXT("UPXPlayerAppearanceComponent::SetDataAsset|PlayerCurrentDA is nullptr"))
		return;
	}
	if (!PlayerDefaultDA)
	{
		UE_LOG(LogAssetData, Warning, TEXT("UPXPlayerAppearanceComponent::SetDataAsset|PlayerDefaultDA is nullptr"))
		return;
	}
	if (!PlayerPuddingDA)
	{
		UE_LOG(LogAssetData, Warning, TEXT("UPXPlayerAppearanceComponent::SetDataAsset|PlayerPuddingDA is nullptr"))
		return;
	}
	if (!PlayerMusicSheetDA)
	{
		UE_LOG(LogAssetData, Warning, TEXT("UPXPlayerAppearanceComponent::SetDataAsset|PlayerMusicSheetDA is nullptr"))
		return;
	}
	if (!PlayerPuddingMusicSheet)
	{
		UE_LOG(LogAssetData, Warning,
		       TEXT("UPXPlayerAppearanceComponent::SetDataAsset|PlayerPuddingMusicSheetDA is nullptr"))
		return;
	}

	switch (PlayerLook)
	{
	case EPlayerLook::Default:
		PlayerCurrentDA = PlayerDefaultDA;
		break;
	case EPlayerLook::Pudding:
		PlayerCurrentDA = PlayerPuddingDA;
		break;
	case EPlayerLook::MusicSheet:
		PlayerCurrentDA = PlayerMusicSheetDA;
		break;
	case EPlayerLook::PuddingMusicSheet:
		PlayerCurrentDA = PlayerPuddingMusicSheet;
		break;
	default:
		break;
	}
}

void UPXPlayerAppearanceComponent::SetFlipbookBasedOnActorForwardVector(const FVector& ActorForwardVector) const
{
	if (!FlipbookComponent)
	{
		UE_LOG(LogComponent, Warning,
		       TEXT("UPXPlayerAppearanceComponent::SetFlipbookBasedOnActorForwardVector|FlipbookComponent is nullptr"))
		return;
	}
	if (!PlayerCurrentDA)
	{
		UE_LOG(LogAssetData, Warning,
		       TEXT("UPXPlayerAppearanceComponent::SetFlipbookBasedOnActorForwardVector|PlayerCurrentDA is nullptr"))
		return;
	}

	if (ActorForwardVector.Equals(FVector::ForwardVector))
	{
		FlipbookComponent->SetFlipbook(PlayerCurrentDA->MoveRightFB);
	}
	else if (ActorForwardVector.Equals(FVector::BackwardVector))
	{
		FlipbookComponent->SetFlipbook(PlayerCurrentDA->MoveLeftFB);
	}
	else if (ActorForwardVector.Equals(FVector::UpVector))
	{
		FlipbookComponent->SetFlipbook(PlayerCurrentDA->MoveUpFB);
	}
	else if (ActorForwardVector.Equals(FVector::DownVector))
	{
		FlipbookComponent->SetFlipbook(PlayerCurrentDA->MoveDownFB);
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
	if (!PlayerCurrentDA)
	{
		UE_LOG(LogAssetData, Warning, TEXT("UPXPlayerAppearanceComponent::SetFlipbookIdle|PlayerCurrentDA is nullptr"))
		return;
	}

	FlipbookComponent->SetFlipbook(PlayerCurrentDA->IdleFB);
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
	if (!PlayerCurrentDA)
	{
		UE_LOG(LogAssetData, Warning,
		       TEXT("UPXPlayerAppearanceComponent::SetFlipbookToGameOver|PlayerCurrentDA is nullptr"))
		return;
	}

	FlipbookComponent->SetFlipbook(PlayerCurrentDA->GameOverFB);
}
