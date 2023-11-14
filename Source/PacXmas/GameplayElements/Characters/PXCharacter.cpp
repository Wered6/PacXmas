// Copyright (c) 2023 Santa Claus. All rights reserved.


#include "PXCharacter.h"
#include "PaperFlipbookComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "PacXmas/DataAssets/Characters/PXCharacterDA.h"

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
}

void APXCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APXCharacter::MoveHorizontal(const float Value)
{
	AddMovementInput(FVector::ForwardVector, Value);

	if (!CharacterDA)
	{
		UE_LOG(LogAssetData, Warning, TEXT("APXCharacter::MoveHorizontal|CharacterDA is nullptr"))
		return;
	}
	if (!FlipbookComp)
	{
		UE_LOG(LogAssetData, Warning, TEXT("APXCharacter::MoveHorizontal|FlipbookComp is nullptr"));
		return;
	}

	const int Sign = FMath::Sign(Value);

	switch (Sign)
	{
	case -1:
		FlipbookComp->SetFlipbook(CharacterDA->LeftWalkFB);
		break;
	case 0:
		FlipbookComp->SetFlipbook(CharacterDA->IdleFB);
		break;
	case 1:
		FlipbookComp->SetFlipbook(CharacterDA->RightWalkFB);
		break;
	}
}

void APXCharacter::MoveVertical(const float Value)
{
	AddMovementInput(FVector::UpVector, Value);

	if (!CharacterDA)
	{
		UE_LOG(LogAssetData, Warning, TEXT("APXCharacter::MoveVertical|CharacterDA is nullptr"));
		return;
	}
	if (!FlipbookComp)
	{
		UE_LOG(LogAssetData, Warning, TEXT("APXCharacter::MoveVertical|FlipbookComp is nullptr"));
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
