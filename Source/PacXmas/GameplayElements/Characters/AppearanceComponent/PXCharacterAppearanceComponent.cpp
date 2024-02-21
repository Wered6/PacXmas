// Copyright (c) 2023 Smoking Carrots. All rights reserved.


#include "PXCharacterAppearanceComponent.h"
#include "PaperFlipbookComponent.h"
#include "PacXmas/DataAssets/Characters/PXCharacterDA.h"
#include "PacXmas/GameplayElements/Characters/MovementComponent/PXCharacterMovementComponent.h"
#include "PacXmas/Utilities/CustomLogs/PXCustomLogs.h"

UPXCharacterAppearanceComponent::UPXCharacterAppearanceComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	FlipbookComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Flipbook Component"));

	FlipbookComponent->SetCollisionProfileName(TEXT("NoCollision"));
	FlipbookComponent->SetUsingAbsoluteRotation(true);
}

void UPXCharacterAppearanceComponent::BeginPlay()
{
	Super::BeginPlay();

	BindChangeStateDelegates();
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

void UPXCharacterAppearanceComponent::InitializeMovementComponent(UPXCharacterMovementComponent* MovementComponent)
{
	if (!MovementComponent)
	{
		UE_LOG(LogComponent, Warning,
		       TEXT("UPXCharacterAppearanceComponent::InitializeMovementComponent|MovementComponent is nullptr"))
		return;
	}

	PXCharacterMovementComponent = MovementComponent;
}

void UPXCharacterAppearanceComponent::BindChangeStateDelegates()
{
	if (!PXCharacterMovementComponent)
	{
		UE_LOG(LogComponent, Warning,
		       TEXT("UPXCharacterAppearanceComponent::BindChangeStateDelegates|PXCharacterMovementComponent is nullptr"
		       ))
		return;
	}
	PXCharacterMovementComponent->OnChangeDirection.BindDynamic(
		this, &UPXCharacterAppearanceComponent::UpdateFlipbookToForwardVector);
	PXCharacterMovementComponent->OnStopMoving.BindDynamic(
		this, &UPXCharacterAppearanceComponent::SetFlipbookIdle);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void UPXCharacterAppearanceComponent::UpdateFlipbookToForwardVector()
{
	if (!FlipbookComponent)
	{
		UE_LOG(LogComponent, Warning,
		       TEXT("UPXCharacterAppearanceComponent::UpdateFlipbookToForwardVector|FlipbookComponent is nullptr"))
		return;
	}
	if (!PXCharacterDA)
	{
		UE_LOG(LogAssetData, Warning,
		       TEXT("UPXCharacterAppearanceComponent::UpdateFlipbookToForwardVector|PXCharacterDA is nullptr"))
		return;
	}
	if (!GetOwner())
	{
		UE_LOG(LogOwner, Warning,
		       TEXT("UPXCharacterAppearanceComponent::UpdateFlipbookToForwardVector|GetOwner() is nullptr"))
		return;
	}

	const FVector ForwardVector = GetOwner()->GetActorForwardVector();


	if (ForwardVector.Equals(FVector::ForwardVector))
	{
		FlipbookComponent->SetFlipbook(PXCharacterDA->GetMoveRightFB());
	}
	else if (ForwardVector.Equals(FVector::BackwardVector))
	{
		FlipbookComponent->SetFlipbook(PXCharacterDA->GetMoveLeftFB());
	}
	else if (ForwardVector.Equals(FVector::UpVector))
	{
		FlipbookComponent->SetFlipbook(PXCharacterDA->GetMoveUpFB());
	}
	else if (ForwardVector.Equals(FVector::DownVector))
	{
		FlipbookComponent->SetFlipbook(PXCharacterDA->GetMoveDownFB());
	}
}

// ReSharper disable once CppMemberFunctionMayBeConst
void UPXCharacterAppearanceComponent::SetFlipbookIdle()
{
	if (!FlipbookComponent)
	{
		UE_LOG(LogComponent, Warning,
		       TEXT("UPXCharacterAppearanceComponent::SetFlipbookIdle|FlipbookComponent is nullptr"))
		return;
	}
	if (!PXCharacterDA)
	{
		UE_LOG(LogAssetData, Warning,
		       TEXT("UPXCharacterAppearanceComponent::SetFlipbookIdle|PXCharacterDA is nullptr"))
		return;
	}

	FlipbookComponent->SetFlipbook(PXCharacterDA->GetIdleFB());
}
