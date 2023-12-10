// Copyright (c) 2023 Santa Claus. All rights reserved.


#include "PXProjectile.h"
#include "PaperSpriteComponent.h"
#include "Components/BoxComponent.h"
#include "MovementComponent/PXProjectileMovementComponent.h"
#include "PacXmas/DataAssets/Projectiles/PXProjectileDA.h"
#include "PacXmas/GameplayElements/Characters/Enemies/PXEnemy.h"
#include "PacXmas/GameplayElements/Effects/VisualEffects/PXSplashedPudding.h"

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

	PaperSpriteComponent->SetSprite(ProjectileDA->UpSprite);
}

void APXProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APXProjectile::SetActorRotationBasedOnLastMoveDirection(const FVector& LastMoveDirection)
{
	FRotator Rotation{FRotator::ZeroRotator};

	if (LastMoveDirection.X > 0)
	{
		Rotation.Pitch = -90.f;
	}
	else if (LastMoveDirection.X < 0)
	{
		Rotation.Pitch = 90.f;
	}
	else if (LastMoveDirection.Z > 0)
	{
		Rotation.Pitch = 0.f;
	}
	else if (LastMoveDirection.Z < 0)
	{
		Rotation.Pitch = 180.f;
	}

	SetActorRotation(Rotation);
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
		// the only thing that Projectile can also overlap (except PXEnemy) is Wall
		Destroy();

		APXSplashedPudding* SplashedPudding = GetWorld()->SpawnActor<APXSplashedPudding>(
			SplashedPuddingClass, FVector::ZeroVector, FRotator::ZeroRotator);

		if (!SplashedPudding)
		{
			UE_LOG(LogActor, Warning, TEXT("APXProjectile::OnOverlapBegin|SplashedPudding is nullptr"))
			return;
		}

		constexpr float LocationOffset{20.f};

		SplashedPudding->SetActorLocationBasedOnSweepResult(SweepResult, LocationOffset);
		SplashedPudding->SetActorRotationBasedOnSweepResult(SweepResult);
	}
}
