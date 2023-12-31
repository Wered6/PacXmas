// Copyright (c) 2023 Smoking Carrots. All rights reserved.


#include "PXProjectilePudding.h"
#include "Components/BoxComponent.h"
#include "PacXmas/GameModes/Gameplay/PXGameModeGameplay.h"
#include "PacXmas/GameplayElements/Characters/Enemies/PXEnemy.h"
#include "PacXmas/GameplayElements/Effects/VisualEffects/PXSplashedPudding.h"
#include "PacXmas/Subsystems/ScoreSubsystem/PXScoreSubsystem.h"
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

void APXProjectilePudding::BeginPlay()
{
	Super::BeginPlay();

	const UGameInstance* GameInstance = GetGameInstance();

	if (!GameInstance)
	{
		UE_LOG(LogGameInstance, Warning, TEXT("APXProjectilePudding::BeginPlay|GameInstance is nullptr"))
		return;
	}

	PXScoreSubsystem = GameInstance->GetSubsystem<UPXScoreSubsystem>();
}

void APXProjectilePudding::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                          UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep,
                                          const FHitResult& SweepResult)
{
	APXEnemy* PXEnemy = Cast<APXEnemy>(OtherActor);

	if (PXEnemy)
	{
		PXEnemy->EatPudding();

		PXScoreSubsystem->AddScore(3);
	}
	// the only thing that Projectile can overlap (except PXEnemy) is Wall
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

		PXScoreSubsystem->SubScore(1);
	}

	SpawnPuddingOnMap();

	Destroy();
}

void APXProjectilePudding::SpawnPuddingOnMap() const
{
	const APXGameModeGameplay* PXGameModeGameplay = GetWorld()->GetAuthGameMode<APXGameModeGameplay>();

	if (!PXGameModeGameplay)
	{
		UE_LOG(LogGameMode, Warning, TEXT("APXProjectilePudding::SpawnPuddingOnMap|PXGameModeGameplay is nullptr"))
		return;
	}

	constexpr float SpawnDelay{10.f};

	PXGameModeGameplay->SpawnPuddingOnMap(SpawnDelay);
}
