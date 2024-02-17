// Copyright (c) 2023 Smoking Carrots. All rights reserved.


#include "PXCharacterAppearanceComponent.h"
#include "PaperFlipbookComponent.h"
#include "PacXmas/DataAssets/Characters/PXCharacterDA.h"
#include "PacXmas/Utilities/CustomLogs/PXCustomLogs.h"

UPXCharacterAppearanceComponent::UPXCharacterAppearanceComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	
	FlipbookComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Flipbook Component"));
	FlipbookComponent->SetCollisionProfileName(TEXT("NoCollision"));
}

void UPXCharacterAppearanceComponent::BeginPlay()
{
	Super::BeginPlay();

	FlipbookComponent->SetUsingAbsoluteRotation(true);
}

void UPXCharacterAppearanceComponent::OnRegister()
{
	Super::OnRegister();

	if (!GetOwner())
	{
		UE_LOG(LogOwner, Warning, TEXT("UPXCharacterAppearanceComponent::OnRegister|GetOwner() is nullptr"))
		return;
	}

	USceneComponent* RootComponent = GetOwner()->GetRootComponent();

	if (!RootComponent)
	{
		UE_LOG(LogComponent, Warning, TEXT("UPXCharacterAppearanceComponent::OnRegister|RootComponent is nullptr"))
		return;
	}

	FlipbookComponent->SetupAttachment(RootComponent);
}

void UPXCharacterAppearanceComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                                    FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
}

void UPXCharacterAppearanceComponent::SetFlipbookBasedOnActorForwardVector(const FVector& ActorForwardVector) const
{
	if (!FlipbookComponent)
	{
		UE_LOG(LogComponent, Warning,
		       TEXT("UPXPlayerAppearanceComponent::SetFlipbookBasedOnActorForwardVector|FlipbookComponent is nullptr"))
		return;
	}
	if (!PXCharacterDA)
	{
		UE_LOG(LogAssetData, Warning,
		       TEXT("UPXPlayerAppearanceComponent::SetFlipbookBasedOnActorForwardVector|PXCharacterDA is nullptr"))
		return;
	}

	if (ActorForwardVector.Equals(FVector::ForwardVector))
	{
		FlipbookComponent->SetFlipbook(PXCharacterDA->GetMoveRightFB());
	}
	else if (ActorForwardVector.Equals(FVector::BackwardVector))
	{
		FlipbookComponent->SetFlipbook(PXCharacterDA->GetMoveLeftFB());
	}
	else if (ActorForwardVector.Equals(FVector::UpVector))
	{
		FlipbookComponent->SetFlipbook(PXCharacterDA->GetMoveUpFB());
	}
	else if (ActorForwardVector.Equals(FVector::DownVector))
	{
		FlipbookComponent->SetFlipbook(PXCharacterDA->GetMoveDownFB());
	}
	// todo add if when FVector::ZeroVector and when stopping change ForwardVector into ZeroVector
}
