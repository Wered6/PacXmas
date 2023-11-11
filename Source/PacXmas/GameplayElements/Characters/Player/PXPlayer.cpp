// Copyright (c) 2023 Santa Claus. All rights reserved.


#include "PXPlayer.h"
#include "Components/BoxComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "PaperFlipbookComponent.h"

APXPlayer::APXPlayer()
{
	PrimaryActorTick.bCanEverTick = false;

	CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collider"));
	RootComponent = CollisionComp;
	CollisionComp->SetCollisionProfileName(TEXT("NoCollision"));

	FlipbookStandingIdle = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("StandingIdle"));
	FlipbookStandingIdle->SetupAttachment(CollisionComp);
	FlipbookStandingIdle->SetCollisionProfileName(TEXT("NoCollision"));

	FloatingPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingPawnMovement"));
}

void APXPlayer::BeginPlay()
{
	Super::BeginPlay();

	CollisionComp->SetCollisionProfileName((TEXT("BlockAll")));
}

void APXPlayer::MoveHorizontal(const float Value)
{
	AddMovementInput(FVector::ForwardVector, Value);
}

void APXPlayer::MoveVertical(const float Value)
{
	AddMovementInput(FVector::UpVector, Value);
}
