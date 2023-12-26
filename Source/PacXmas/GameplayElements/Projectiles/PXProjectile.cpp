// Copyright (c) 2023 Santa Claus. All rights reserved.


#include "PXProjectile.h"
#include "PaperSpriteComponent.h"
#include "Components/BoxComponent.h"
#include "MovementComponent/PXProjectileMovementComponent.h"
#include "PacXmas/DataAssets/Projectiles/PXProjectileDA.h"
#include "PacXmas/Utilities/CustomLogs/PXCustomLogs.h"

APXProjectile::APXProjectile()
{
	CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Box"));
	RootComponent = CollisionComponent;
	CollisionComponent->SetCollisionProfileName(TEXT("Projectile"));

	PaperSpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Paper Sprite"));
	PaperSpriteComponent->SetupAttachment(CollisionComponent);
	PaperSpriteComponent->SetCollisionProfileName(TEXT("NoCollision"));

	ProjectileMovementComponent = CreateDefaultSubobject<UPXProjectileMovementComponent>(TEXT("Movement Component"));

	const FVector BoxExtent = FVector(CollisionSize / 2);
	CollisionComponent->SetBoxExtent(BoxExtent);
}

void APXProjectile::BeginPlay()
{
	Super::BeginPlay();

	if (!ProjectileMovementComponent)
	{
		UE_LOG(LogComponent, Warning, TEXT("APXProjectile::BeginPlay|ProjectileMovementComponent is nullptr"))
		return;
	}
	if (!ProjectileDA)
	{
		UE_LOG(LogAssetData, Warning, TEXT("APXProjectile::BeginPlay|ProjectileDA is nullptr"))
		return;
	}

	PaperSpriteComponent->SetSprite(ProjectileDA->ProjectileSprite);
}
