// Copyright (c) 2023 Santa Claus. All rights reserved.


#include "PXSpawnItemsSubsystem.h"
#include "EngineUtils.h"
#include "PacXmas/GameplayElements/Items/Pudding/PXPudding.h"
#include "SpawnPoint/Pudding/PXPuddingSpawnPoint.h"

void UPXSpawnItemsSubsystem::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);

	InitializePuddingSpawnPointsArray();
}

void UPXSpawnItemsSubsystem::SpawnMusicSheet()
{
}

void UPXSpawnItemsSubsystem::SpawnPudding(const TSubclassOf<APXPudding> PuddingClass, const float SpawnDelay)
{
	if (PuddingSpawnPoints.Num() > 0)
	{
		const uint8_t RandomIndex = FMath::RandRange(0, PuddingSpawnPoints.Num() - 1);
		const APXPuddingSpawnPoint* PuddingSpawnPoint = PuddingSpawnPoints[RandomIndex];

		if (!PuddingSpawnPoint)
		{
			UE_LOG(LogActor, Warning, TEXT("UPXSpawnItemsSubsystem::SpawnPudding|PuddingSpawnPoint is nullptr"))
			return;
		}

		const FVector SpawnLocation = PuddingSpawnPoint->GetActorLocation();
		FTimerHandle TimerHandle;
		FTimerDelegate TimerDelegate;
		TimerDelegate.BindUFunction(this, FName("DelayedSpawnPudding"), PuddingClass, SpawnLocation);
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, SpawnDelay, false);
	}
}

void UPXSpawnItemsSubsystem::SpawnFireworks()
{
}

void UPXSpawnItemsSubsystem::InitializePuddingSpawnPointsArray()
{
	for (TActorIterator<APXPuddingSpawnPoint> It(GetWorld()); It; ++It)
	{
		APXPuddingSpawnPoint* NewPuddingSpawnPoint = *It;
		if (IsValid(NewPuddingSpawnPoint))
		{
			PuddingSpawnPoints.Add(NewPuddingSpawnPoint);
		}
	}
}

void UPXSpawnItemsSubsystem::DelayedSpawnPudding(const TSubclassOf<APXPudding> PuddingClass,
                                                 const FVector& SpawnLocation)
{
	if (!PuddingClass)
	{
		UE_LOG(LogClass, Warning, TEXT("UPXSpawnItemsSubsystem::DelayedSpawnPudding|PuddingClass is nullptr"))
		return;
	}

	GetWorld()->SpawnActor<APXPudding>(PuddingClass, SpawnLocation, FRotator::ZeroRotator);
}
