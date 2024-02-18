// Copyright (c) 2023 Smoking Carrots. All rights reserved.


#include "PXProjectilePudding.h"
#include "Components/BoxComponent.h"
#include "PacXmas/GameInstance/PXGameInstance.h"
#include "PacXmas/GameModes/Gameplay/PXGameModeGameplay.h"
#include "PacXmas/GameplayElements/Characters/Enemies/PXEnemy.h"
#include "PacXmas/GameplayElements/Effects/VisualEffects/PXSplashedPudding.h"
#include "PacXmas/GameplayElements/Portal/PXPortal.h"
#include "PacXmas/Subsystems/ScoreSubsystem/PXScoreSubsystem.h"
#include "PacXmas/UI/HUD/PXHUD.h"
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

	InitializeScoreSubsystem();
}

void APXProjectilePudding::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                          UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep,
                                          const FHitResult& SweepResult)
{
	APXEnemy* PXEnemy = Cast<APXEnemy>(OtherActor);
	const APXPortal* PXPortal = Cast<APXPortal>(OtherActor);

	if (PXEnemy)
	{
		PXEnemy->EatPudding();
		AddAndPopupScore(EScoreTypes::HitPudding);
	}
	else if (PXPortal)
	{
		return;
	}
	// Last thing it can overlap with is wall
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

		AddAndPopupScore(EScoreTypes::MissPudding);
	}

	SpawnPuddingOnMap();

	Destroy();
	// todo add different sounds for hitting devil and hitting wall
}

void APXProjectilePudding::InitializeScoreSubsystem()
{
	const UPXGameInstance* PXGameInstance = Cast<UPXGameInstance>(GetGameInstance());

	if (!PXGameInstance)
	{
		UE_LOG(LogGameInstance, Warning,
		       TEXT("APXProjectilePudding::InitializeScoreSubsystem|PXGameInstance is nullptr"))
		return;
	}

	PXScoreSubsystem = PXGameInstance->GetSubsystem<UPXScoreSubsystem>();
}

void APXProjectilePudding::AddAndPopupScore(const EScoreTypes ScoreType) const
{
	if (!PXScoreSubsystem)
	{
		UE_LOG(LogSubsystem, Warning, TEXT("APXProjectilePudding::AddAndPopupScoreHit|PXScoreSubsystem is nullptr"))
		return;
	}

	const APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

	if (!PlayerController)
	{
		UE_LOG(LogController, Warning, TEXT("APXProjectilePudding::AddAndPopupScoreHit|PlayerController is nullptr"))
		return;
	}

	APXHUD* PXHUD = Cast<APXHUD>(PlayerController->GetHUD());

	if (!PXHUD)
	{
		UE_LOG(LogHUD, Warning, TEXT("APXProjectilePudding::AddAndPopupScoreHit|PXHUD is nullptr"))
		return;
	}

	PXScoreSubsystem->AddScore(ScoreType);
	PXHUD->DisplayScorePopup(ScoreType);
	PXHUD->UpdateScore();
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
