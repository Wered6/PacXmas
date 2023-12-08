// Copyright (c) 2023 Santa Claus. All rights reserved.


#include "PXProjectile.h"
#include "PaperSpriteComponent.h"
#include "Components/BoxComponent.h"
#include "MovementComponent/PXProjectileMovementComponent.h"
#include "PacXmas/DataAssets/Projectiles/PXProjectileDA.h"
#include "PacXmas/GameplayElements/Characters/Enemies/PXEnemy.h"
#include "PacXmas/Utilities/CustomLogs/PXCustomLogs.h"

APXProjectile::APXProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Box"));
	RootComponent = CollisionComponent;
	CollisionComponent->SetCollisionProfileName(TEXT("Projectile"));

	PaperSpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Paper Sprite"));
	PaperSpriteComponent->SetupAttachment(CollisionComponent);
	PaperSpriteComponent->SetCollisionProfileName(TEXT("NoCollision"));

	const FVector BoxExtent = FVector(CollisionWidth / 2, CollisionDepth / 2, CollisionHeight / 2);
	CollisionComponent->SetBoxExtent(BoxExtent);
	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &APXProjectile::OnOverlapBegin);

	ProjectileMovementComponent = CreateDefaultSubobject<UPXProjectileMovementComponent>(TEXT("Movement Component"));
}

void APXProjectile::BeginPlay()
{
	Super::BeginPlay();

	if (!PaperSpriteComponent)
	{
		UE_LOG(LogComponent, Warning, TEXT("APXProjectile::BeginPlay|PaperSpriteComponent is nullptr"))
		return;
	}
	if (!ProjectileDA)
	{
		UE_LOG(LogAssetData, Warning, TEXT("APXProjectile::BeginPlay|ProjectileDA is nullptr"))
		return;;
	}
}

void APXProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

UPXProjectileMovementComponent* APXProjectile::GetMovementComponent() const
{
	return ProjectileMovementComponent;
}

void APXProjectile::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                   UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep,
                                   const FHitResult& SweepResult)
{
	APXEnemy* PXEnemy = Cast<APXEnemy>(OtherActor);
	if (PXEnemy)
	{
		PXEnemy->EatPudding();

		Destroy();
	}
	else
	{
		// the only thing that Projectile can also overlap (beside PXEnemy) is Wall
		Destroy();
	}
}

void APXProjectile::ChangeSprite(const FVector& Direction) const
{
	if (Direction.X > 0)
	{
		PaperSpriteComponent->SetSprite(ProjectileDA->RightSprite);
		UE_LOG(LogTemp, Warning, TEXT("Direction: %s"), *Direction.ToString())
	}
	else if (Direction.X < 0)
	{
		PaperSpriteComponent->SetSprite(ProjectileDA->LeftSprite);
		UE_LOG(LogTemp, Warning, TEXT("Direction: %s"), *Direction.ToString())
	}
	else if (Direction.Z > 0)
	{
		PaperSpriteComponent->SetSprite(ProjectileDA->UpSprite);
		UE_LOG(LogTemp, Warning, TEXT("Direction: %s"), *Direction.ToString())
	}
	else if (Direction.Z < 0)
	{
		PaperSpriteComponent->SetSprite(ProjectileDA->DownSprite);
		UE_LOG(LogTemp, Warning, TEXT("Direction: %s"), *Direction.ToString())
	}
}
