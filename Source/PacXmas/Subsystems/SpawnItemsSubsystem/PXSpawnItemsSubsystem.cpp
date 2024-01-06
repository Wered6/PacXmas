// Copyright (c) 2023 Smoking Carrots. All rights reserved.


#include "PXSpawnItemsSubsystem.h"
#include "EngineUtils.h"
#include "PacXmas/GameplayElements/Items/Fireworks/PXFireworks.h"
#include "PacXmas/GameplayElements/Items/MusicSheet/PXMusicSheet.h"
#include "PacXmas/GameplayElements/Items/Pudding/PXPudding.h"
#include "PacXmas/GameplayElements/SpawnPoints/Fireworks/PXFireworksSpawnPoint.h"
#include "PacXmas/GameplayElements/SpawnPoints/MusicSheet/PXMusicSheetSpawnPoint.h"
#include "PacXmas/GameplayElements/SpawnPoints/Pudding/PXPuddingSpawnPoint.h"

void UPXSpawnItemsSubsystem::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);

	InitializePuddingSpawnPointsArray();
	InitializeMusicSheetSpawnPointsArray();
	InitializeFireworksSpawnPointsArray();
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
		if (!PuddingClass)
		{
			UE_LOG(LogClass, Warning, TEXT("UPXSpawnItemsSubsystem::SpawnPudding|PuddingClass is nullptr"))
			return;
		}

		const FVector SpawnLocation = PuddingSpawnPoint->GetActorLocation();
		FTimerHandle TimerHandle;
		FTimerDelegate TimerDelegate;
		TimerDelegate.BindUFunction(this, FName("DelayedSpawnPudding"), PuddingClass, SpawnLocation);
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, SpawnDelay, false);
	}
}

void UPXSpawnItemsSubsystem::SpawnMusicSheet(const TSubclassOf<APXMusicSheet> MusicSheetClass)
{
	constexpr uint8_t MaxMusicSheetSpawns{4};

	if (MusicSheetSpawnPoints.Num() > 0 && MusicSheetSpawnedCount < MaxMusicSheetSpawns)
	{
		MusicSheetSpawnedCount++;

		const uint8_t RandomIndex = FMath::RandRange(0, MusicSheetSpawnPoints.Num() - 1);
		const APXMusicSheetSpawnPoint* MusicSheetSpawnPoint = MusicSheetSpawnPoints[RandomIndex];

		if (!MusicSheetSpawnPoint)
		{
			UE_LOG(LogActor, Warning, TEXT("UPXSpawnItemsSubsystem::SpawnMusicSheet|MusicSheetSpawnPoint is nullptr"))
			return;
		}
		if (!MusicSheetClass)
		{
			UE_LOG(LogClass, Warning, TEXT("UPXSpawnItemsSubsystem::SpawnMusicSheet|MusicSheetClass is nullptr"))
			return;
		}

		const FVector SpawnLocation = MusicSheetSpawnPoint->GetActorLocation();

		GetWorld()->SpawnActor<APXMusicSheet>(MusicSheetClass, SpawnLocation, FRotator::ZeroRotator);
	}
}

void UPXSpawnItemsSubsystem::SpawnAllFireworks(const TSubclassOf<APXFireworks> FireworksClass)
{
	if (!FireworksClass)
	{
		UE_LOG(LogClass, Warning, TEXT("UPXSpawnItemsSubsystem::SpawnAllFireworks|FireworksClass is nullptr"))
		return;
	}

	for (const APXFireworksSpawnPoint* FireworksSpawnPoint : FireworksSpawnPoints)
	{
		if (!FireworksSpawnPoint)
		{
			UE_LOG(LogActor, Warning, TEXT("UPXSpawnItemsSubsystem::SpawnAllFireworks|FireworksSpawnPoint is nullptr"))
			return;
		}

		const FVector SpawnLocation = FireworksSpawnPoint->GetActorLocation();

		GetWorld()->SpawnActor<APXFireworks>(FireworksClass, SpawnLocation, FRotator::ZeroRotator);
	}
}

void UPXSpawnItemsSubsystem::RespawnFireworks(const TSubclassOf<APXFireworks> FireworksClass, const float SpawnDelay,
                                              const FVector& SpawnLocation)
{
	if (FireworksSpawnPoints.Num() > 0)
	{
		FTimerHandle TimerHandle;
		FTimerDelegate TimerDelegate;
		TimerDelegate.BindUFunction(this, FName("DelayedSpawnFireworks"), FireworksClass, SpawnLocation);
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, SpawnDelay, false);
	}
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

void UPXSpawnItemsSubsystem::InitializeMusicSheetSpawnPointsArray()
{
	for (TActorIterator<APXMusicSheetSpawnPoint> It(GetWorld()); It; ++It)
	{
		APXMusicSheetSpawnPoint* NewMusicSheetSpawnPoint = *It;
		if (IsValid(NewMusicSheetSpawnPoint))
		{
			MusicSheetSpawnPoints.Add(NewMusicSheetSpawnPoint);
		}
	}
}

void UPXSpawnItemsSubsystem::InitializeFireworksSpawnPointsArray()
{
	for (TActorIterator<APXFireworksSpawnPoint> It(GetWorld()); It; ++It)
	{
		APXFireworksSpawnPoint* NewFireworksSpawnPoint = *It;
		if (IsValid(NewFireworksSpawnPoint))
		{
			FireworksSpawnPoints.Add(NewFireworksSpawnPoint);
		}
	}
}

// ReSharper disable once CppMemberFunctionMayBeConst
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

// ReSharper disable once CppMemberFunctionMayBeConst
void UPXSpawnItemsSubsystem::DelayedSpawnFireworks(const TSubclassOf<APXFireworks> FireworksClass,
                                                   const FVector& SpawnLocation)
{
	if (!FireworksClass)
	{
		UE_LOG(LogClass, Warning, TEXT("UPXSpawnItemsSubsystem::DelayedSpawnFireworks|FireworksClass is nullptr"))
		return;
	}

	GetWorld()->SpawnActor<APXFireworks>(FireworksClass, SpawnLocation, FRotator::ZeroRotator);
}
