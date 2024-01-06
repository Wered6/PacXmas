// Copyright (c) 2023 Smoking Carrots. All rights reserved.


#include "PXSplashedPudding.h"
#include "PaperSpriteComponent.h"
#include "PacXmas/DataAssets/VisualEffects/PXSplashedPuddingDA.h"
#include "PacXmas/Utilities/CustomLogs/PXCustomLogs.h"

APXSplashedPudding::APXSplashedPudding()
{
	PaperSpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Paper Sprite"));
	RootComponent = PaperSpriteComponent;
	PaperSpriteComponent->SetCollisionProfileName(TEXT("NoCollision"));
}

void APXSplashedPudding::SetRotationRelativeToProjectileDirection(const FVector& ProjectileForwardVector)
{
	const FVector OppositeDirection = -ProjectileForwardVector;
	const FRotator SplashedPuddingRotation = OppositeDirection.Rotation();

	SetActorRotation(SplashedPuddingRotation);
}

void APXSplashedPudding::SetLocationRelativeToProjectile(const FVector& ProjectileForwardVector,
                                                         const FVector& ProjectileLocation)
{
	constexpr float LocationOffset{20.f};
	const FVector SplashedPuddingLocation = ProjectileLocation + ProjectileForwardVector * LocationOffset;

	SetActorLocation(SplashedPuddingLocation);
}

void APXSplashedPudding::BeginPlay()
{
	Super::BeginPlay();

	if (!PaperSpriteComponent)
	{
		UE_LOG(LogComponent, Warning, TEXT("APXSplashedPudding::BeginPlay|PaperSpriteComponent is nullptr"))
		return;
	}
	if (!SplashedPuddingDA)
	{
		UE_LOG(LogAssetData, Warning, TEXT("APXSplashedPudding::BeginPlay|SplashedPuddingDA is nullptr"))
		return;
	}

	PaperSpriteComponent->SetSprite(SplashedPuddingDA->SplashedPuddingSprite);
}
