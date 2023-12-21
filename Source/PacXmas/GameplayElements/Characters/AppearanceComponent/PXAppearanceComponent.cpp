// Copyright (c) 2023 Santa Claus. All rights reserved.


#include "PXAppearanceComponent.h"
#include "PaperFlipbookComponent.h"
#include "PacXmas/DataAssets/Characters/PXCharacterDA.h"
#include "PacXmas/Utilities/CustomLogs/PXCustomLogs.h"

UPXAppearanceComponent::UPXAppearanceComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	FlipbookComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Flipbook Component"));
	FlipbookComponent->SetCollisionProfileName(TEXT("NoCollision"));
}

void UPXAppearanceComponent::BeginPlay()
{
	Super::BeginPlay();

	if (!CharacterDA)
	{
		UE_LOG(LogAssetData, Warning, TEXT("UPXAppearanceComponent::BeginPlay|CharacterDA is nullptr"))
		return;
	}

	ActiveDA = CharacterDA;

	if (!FlipbookComponent)
	{
		UE_LOG(LogComponent, Warning, TEXT("UPXAppearanceComponent::BeginPlay|FlipbookComponent is nullptr"))
		return;
	}
	if (!ActiveDA)
	{
		UE_LOG(LogAssetData, Warning, TEXT("UPXAppearanceComponent::BeginPlay|ActiveDA is nullptr"))
		return;
	}

	FlipbookComponent->SetFlipbook(ActiveDA->IdleFB);
}

void UPXAppearanceComponent::OnRegister()
{
	Super::OnRegister();

	if (!GetOwner())
	{
		UE_LOG(LogActor, Warning, TEXT("UPXAppearanceComponent::OnRegister|GetOwner() is nullptr"))
		return;
	}

	FlipbookComponent->SetupAttachment(GetOwner()->GetRootComponent());
}

void UPXAppearanceComponent::SetFlipbookBasedOnAxis(const int8 Sign, const EAxisMovement Axis) const
{
	switch (Axis)
	{
	case EAxisMovement::Horizontal:
		{
			switch (Sign)
			{
			case -1:
				SetFlipbookBasedOnDirection(ECharacterDirection::Left);
				break;
			case 1:
				SetFlipbookBasedOnDirection(ECharacterDirection::Right);
				break;
			}
			break;
		}
	case EAxisMovement::Vertical:
		{
			switch (Sign)
			{
			case -1:
				SetFlipbookBasedOnDirection(ECharacterDirection::Down);
				break;
			case 1:
				SetFlipbookBasedOnDirection(ECharacterDirection::Up);
				break;
			}
			break;
		}
	}
}

void UPXAppearanceComponent::SetFlipbookBasedOnDirection(const ECharacterDirection Direction) const
{
	if (!FlipbookComponent)
	{
		UE_LOG(LogComponent, Warning,
		       TEXT("UPXAppearanceComponent::SetFlipbookBasedOnDirection|FlipbookComponent is nullptr"))
		return;
	}
	if (!ActiveDA)
	{
		UE_LOG(LogAssetData, Warning, TEXT("UPXAppearanceComponent::SetFlipbookBasedOnDirection|ActiveDA is nullptr"))
		return;
	}

	switch (Direction)
	{
	case ECharacterDirection::Idle:
		FlipbookComponent->SetFlipbook(ActiveDA->IdleFB);
		break;
	case ECharacterDirection::Up:
		FlipbookComponent->SetFlipbook(ActiveDA->WalkUpFB);
		break;
	case ECharacterDirection::Right:
		FlipbookComponent->SetFlipbook(ActiveDA->WalkRightFB);
		break;
	case ECharacterDirection::Down:
		FlipbookComponent->SetFlipbook(ActiveDA->WalkDownFB);
		break;
	case ECharacterDirection::Left:
		FlipbookComponent->SetFlipbook(ActiveDA->WalkLeftFB);
		break;
	default:
		break;
	}
}
