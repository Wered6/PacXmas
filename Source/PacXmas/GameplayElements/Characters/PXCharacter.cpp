// Copyright (c) 2023 Santa Claus. All rights reserved.


#include "PXCharacter.h"
#include "PaperFlipbookComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "PacXmas/DataAssets/Characters/PXCharacterDA.h"
#include "PacXmas/Utilities/CustomLogs/PXCustomLogs.h"

APXCharacter::APXCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collider"));
	RootComponent = CollisionComponent;
	CollisionComponent->SetCollisionProfileName(TEXT("BlockAllDynamic"));

	FlipbookComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Appearance"));
	FlipbookComponent->SetupAttachment(CollisionComponent);
	FlipbookComponent->SetCollisionProfileName(TEXT("NoCollision"));

	FloatingPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingPawnMovement"));

	const FVector BoxExtent = FVector(CollisionWidth / 2, CollisionDepth / 2, CollisionHeight / 2);
	CollisionComponent->SetBoxExtent(BoxExtent);
}

void APXCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (!CharacterDA)
	{
		UE_LOG(LogCharacter, Warning, TEXT("APXCharacter::BeginPlay|CharacterDA is nullptr"))
		return;
	}
	
	ActiveDA = CharacterDA;

	if (!FlipbookComponent)
	{
		UE_LOG(LogCharacter, Warning, TEXT("APXCharacter::BeginPlay|FlipbookComp is nullptr"))
		return;
	}
	if (!ActiveDA)
	{
		UE_LOG(LogCharacter, Warning, TEXT("APXCharacter::BeginPlay|ActiveDA is nullptr"))
		return;
	}

	FlipbookComponent->SetFlipbook(ActiveDA->IdleFB);
}

void APXCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APXCharacter::MoveHorizontal(const float Value)
{
	AddMovementInput(FVector::ForwardVector, Value);

	if (!FlipbookComponent)
	{
		UE_LOG(LogCharacter, Warning, TEXT("APXCharacter::MoveHorizontal|FlipbookComp is nullptr"))
		return;
	}
	if (!ActiveDA)
	{
		UE_LOG(LogCharacter, Warning, TEXT("APXCharacter::MoveHorizontal|ActiveDA is nullptr"))
		return;
	}

	const int Sign = FMath::Sign(Value);

	switch (Sign)
	{
	case -1:
		FlipbookComponent->SetFlipbook(ActiveDA->LeftWalkFB);
		break;
	case 1:
		FlipbookComponent->SetFlipbook(ActiveDA->RightWalkFB);
		break;
	}
}

void APXCharacter::MoveVertical(const float Value)
{
	AddMovementInput(FVector::UpVector, Value);

	if (!FlipbookComponent)
	{
		UE_LOG(LogCharacter, Warning, TEXT("APXCharacter::MoveVertical|FlipbookComp is nullptr"))
		return;
	}
	if (!ActiveDA)
	{
		UE_LOG(LogCharacter, Warning, TEXT("APXCharacter::MoveVertical|ActiveDA is nullptr"))
		return;
	}

	const int Sign = FMath::Sign(Value);

	switch (Sign)
	{
	case -1:
		FlipbookComponent->SetFlipbook(ActiveDA->DownWalkFB);
		break;
	case 1:
		FlipbookComponent->SetFlipbook(ActiveDA->UpWalkFB);
		break;
	}
}

void APXCharacter::SetFlipbookToIdle() const
{
	// if (!FlipbookComponent)
	// {
	// 	UE_LOG(LogCharacter, Warning, TEXT("APXCharacter::SetFlipbookToIdle|FlipbookComponent is nullptr"))
	// 	return;
	// }

	if (FlipbookComponent->GetFlipbook() != ActiveDA->IdleFB)
	{
		if (!ActiveDA)
		{
			UE_LOG(LogCharacter, Warning, TEXT("APXCharacter::SetFlipbookToIdle|ActiveDA is nullptr"))
			return;
		}

		FlipbookComponent->SetFlipbook(ActiveDA->IdleFB);
	}
}
