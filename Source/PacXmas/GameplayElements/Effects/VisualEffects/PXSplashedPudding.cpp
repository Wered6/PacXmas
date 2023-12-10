// Copyright (c) 2023 Santa Claus. All rights reserved.


#include "PXSplashedPudding.h"
#include "PaperSpriteComponent.h"
#include "PacXmas/DataAssets/VisualEffects/PXSplashedPuddingDA.h"
#include "PacXmas/Utilities/CustomLogs/PXCustomLogs.h"

APXSplashedPudding::APXSplashedPudding()
{
	PrimaryActorTick.bCanEverTick = false;

	PaperSpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Paper Sprite"));
	RootComponent = PaperSpriteComponent;
	PaperSpriteComponent->SetCollisionProfileName(TEXT("NoCollision"));
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

	PaperSpriteComponent->SetSprite(SplashedPuddingDA->Sprite);
}

void APXSplashedPudding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APXSplashedPudding::SetActorRotationBasedOnSweepResult(const FHitResult& SweepResult)
{
	const FVector ImpactNormal = SweepResult.ImpactNormal;
	FRotator Rotation = FRotator::ZeroRotator;

	if (ImpactNormal.X > 0)
	{
		Rotation.Pitch = -90.f;
	}
	else if (ImpactNormal.X < 0)
	{
		Rotation.Pitch = 90.f;
	}
	else if (ImpactNormal.Z > 0)
	{
		Rotation.Pitch = 0.f;
	}
	else if (ImpactNormal.Z < 0)
	{
		Rotation.Pitch = 180.f;
	}

	SetActorRotation(Rotation);
}

void APXSplashedPudding::SetActorLocationBasedOnSweepResult(const FHitResult& SweepResult, const float& Offset)
{
	const FVector ImpactNormal = SweepResult.ImpactNormal;
	FVector Location = SweepResult.Location;

	if (ImpactNormal.X > 0)
	{
		Location.X -= Offset;
	}
	else if (ImpactNormal.X < 0)
	{
		Location.X += Offset;
	}
	else if (ImpactNormal.Z > 0)
	{
		Location.Z -= Offset;
	}
	else if (ImpactNormal.Z < 0)
	{
		Location.Z += Offset;
	}

	SetActorLocation(Location);
}
