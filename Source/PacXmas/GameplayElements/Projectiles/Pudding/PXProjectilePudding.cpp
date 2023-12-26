// Copyright (c) 2023 Santa Claus. All rights reserved.


#include "PXProjectilePudding.h"
#include "Components/BoxComponent.h"
#include "PacXmas/GameplayElements/Characters/Enemies/PXEnemy.h"
#include "PacXmas/GameplayElements/Effects/VisualEffects/PXSplashedPudding.h"
#include "PacXmas/Utilities/CustomLogs/PXCustomLogs.h"

APXProjectilePudding::APXProjectilePudding()
{
	if (!CollisionComponent)
	{
		UE_LOG(LogComponent, Warning, TEXT("APXProjectilePudding::APXProjectilePudding|CollisionComponent is nullptr"))
		return;
	}

	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &APXProjectilePudding::OnOverlapBegin);
}

void APXProjectilePudding::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                          UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep,
                                          const FHitResult& SweepResult)
{
	APXEnemy* PXEnemy = Cast<APXEnemy>(OtherActor);

	if (PXEnemy)
	{
		PXEnemy->EatPudding(SweepResult);
	}
	// the only thing that Projectile can also overlap (except PXEnemy) is Wall
	else
	{
		APXSplashedPudding* SplashedPudding = GetWorld()->SpawnActor<APXSplashedPudding>(
			SplashedPuddingClass, FVector::ZeroVector, FRotator::ZeroRotator);

		if (!SplashedPudding)
		{
			UE_LOG(LogActor, Warning, TEXT("APXProjectile::OnOverlapBegin|SplashedPudding is nullptr"))
			return;
		}


		const FVector ProjectileForwardVector = GetActorForwardVector();
		const FVector ProjectileLocation = GetActorLocation();

		SplashedPudding->SetRotationRelativeToProjectileDirection(ProjectileForwardVector);
		SplashedPudding->SetLocationRelativeToProjectile(ProjectileForwardVector, ProjectileLocation);
	}
	Destroy();
}
