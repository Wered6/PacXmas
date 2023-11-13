// Copyright (c) 2023 Santa Claus. All rights reserved.


#include "PXPlayer.h"
#include "Components/BoxComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "PaperFlipbookComponent.h"
#include "PacXmas/DataAssets/Characters/Player/Girl/PXGirlDA.h"

APXPlayer::APXPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collider"));
	RootComponent = CollisionComp;
	CollisionComp->SetCollisionProfileName(TEXT("BlockAll"));

	Flipbook = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("StandingIdle"));
	Flipbook->SetupAttachment(CollisionComp);
	Flipbook->SetCollisionProfileName(TEXT("NoCollision"));

	FloatingPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingPawnMovement"));
}

void APXPlayer::BeginPlay()
{
	Super::BeginPlay();
}

void APXPlayer::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (GetVelocity().IsZero())
	{
		if (GirlDA && Flipbook && Flipbook->GetFlipbook() != GirlDA->IdleFB)
		{
			Flipbook->SetFlipbook(GirlDA->IdleFB);
		}
	}
}

void APXPlayer::MoveHorizontal(const float Value)
{
	AddMovementInput(FVector::ForwardVector, Value);

	if (!GirlDA)
	{
		UE_LOG(LogAssetData, Warning, TEXT("APXPlayer::MoveHorizontal|GirlDA is nullptr"));
		return;
	}
	if (!Flipbook)
	{
		UE_LOG(LogAssetData, Warning, TEXT("APXPlayer::MoveHorizontal|Flipbook is nullptr"));
		return;
	}

	const int Sign = FMath::Sign(Value);

	switch (Sign)
	{
	case -1:
		Flipbook->SetFlipbook(GirlDA->LeftWalkFB);
		break;
	case 1:
		Flipbook->SetFlipbook(GirlDA->RightWalkFB);
		break;
	}
}

void APXPlayer::MoveVertical(const float Value)
{
	AddMovementInput(FVector::UpVector, Value);

	if (!GirlDA)
	{
		UE_LOG(LogAssetData, Warning, TEXT("APXPlayer::MoveVertical|GirlDA is nullptr"));
		return;
	}
	if (!Flipbook)
	{
		UE_LOG(LogAssetData, Warning, TEXT("APXPlayer::MoveVertical|Flipbook is nullptr"));
		return;
	}

	const int Sign = FMath::Sign(Value);

	switch (Sign)
	{
	case -1:
		Flipbook->SetFlipbook(GirlDA->DownWalkFB);
		break;
	case 1:
		Flipbook->SetFlipbook(GirlDA->UpWalkFB);
		break;
	}
}
