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

	CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collider"));
	RootComponent = CollisionComp;
	CollisionComp->SetCollisionProfileName(TEXT("BlockAllDynamic"));

	FlipbookComp = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Appearance"));
	FlipbookComp->SetupAttachment(CollisionComp);
	FlipbookComp->SetCollisionProfileName(TEXT("NoCollision"));

	FloatingPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingPawnMovement"));

	const FVector BoxExtent = FVector(CollisionWidth / 2, CollisionDepth / 2, CollisionHeight / 2);
	CollisionComp->SetBoxExtent(BoxExtent);
}

void APXCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (!FlipbookComp)
	{
		UE_LOG(LogCharacter, Warning, TEXT("APXCharacter::BeginPlay|FlipbookComp is nullptr"));
		return;
	}
	if (!CharacterDA)
	{
		UE_LOG(LogCharacter, Warning, TEXT("APXCharacter::BeginPlay|CharacterDA is nullptr"));
		return;
	}

	FlipbookComp->SetFlipbook(CharacterDA->IdleFB);
}

void APXCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bIsPlayerInputActive && GetVelocity().IsNearlyZero())
	{
		if (FlipbookComp && CharacterDA && FlipbookComp->GetFlipbook() != CharacterDA->IdleFB)
		{
			FlipbookComp->SetFlipbook(CharacterDA->IdleFB);
		}
	}

	bIsPlayerInputActive = false;
}

void APXCharacter::MoveHorizontal(const float Value)
{
	if (Value != 0)
	{
		bIsPlayerInputActive = true;

		AddMovementInput(FVector::ForwardVector, Value);

		if (!FlipbookComp)
		{
			UE_LOG(LogCharacter, Warning, TEXT("APXCharacter::MoveHorizontal|FlipbookComp is nullptr"));
			return;
		}
		if (!CharacterDA)
		{
			UE_LOG(LogCharacter, Warning, TEXT("APXCharacter::MoveHorizontal|CharacterDA is nullptr"))
			return;
		}

		const int Sign = FMath::Sign(Value);

		switch (Sign)
		{
		case -1:
			FlipbookComp->SetFlipbook(CharacterDA->LeftWalkFB);
			break;
		case 1:
			FlipbookComp->SetFlipbook(CharacterDA->RightWalkFB);
			break;
		}
	}
}

void APXCharacter::MoveVertical(const float Value)
{
	if (Value != 0)
	{
		bIsPlayerInputActive = true;

		AddMovementInput(FVector::UpVector, Value);

		if (!FlipbookComp)
		{
			UE_LOG(LogCharacter, Warning, TEXT("APXCharacter::MoveVertical|FlipbookComp is nullptr"));
			return;
		}
		if (!CharacterDA)
		{
			UE_LOG(LogCharacter, Warning, TEXT("APXCharacter::MoveVertical|CharacterDA is nullptr"));
			return;
		}

		const int Sign = FMath::Sign(Value);

		switch (Sign)
		{
		case -1:
			FlipbookComp->SetFlipbook(CharacterDA->DownWalkFB);
			break;
		case 1:
			FlipbookComp->SetFlipbook(CharacterDA->UpWalkFB);
			break;
		}
	}
}
