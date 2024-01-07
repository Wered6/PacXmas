// Copyright (c) 2023 Smoking Carrots. All rights reserved.


#include "PXGameModeGameplay.h"
#include "Kismet/GameplayStatics.h"
#include "PacXmas/GameInstance/PXGameInstance.h"
#include "PacXmas/GameplayElements/Characters/Player/PXPlayer.h"
#include "PacXmas/GameplayElements/Items/Fireworks/PXFireworks.h"
#include "PacXmas/GameplayElements/Items/MusicSheet/PXMusicSheet.h"
#include "PacXmas/GameplayElements/Items/Pudding/PXPudding.h"
#include "PacXmas/Subsystems/SpawnItemsSubsystem/PXSpawnItemsSubsystem.h"
#include "PacXmas/Utilities/CustomLogs/PXCustomLogs.h"

void APXGameModeGameplay::BeginPlay()
{
	Super::BeginPlay();

	InitializePXSpawnItemsSubsystem();

	SpawnPuddingOnMap();
	SpawnMusicSheetOnMap();
	SpawnAllFireworks();

	BindHandleGameOver();
}

void APXGameModeGameplay::RestartPlayerAtPlayerStart(AController* NewPlayer, AActor* StartSpot)
{
	if (!NewPlayer)
	{
		UE_LOG(LogController, Warning, TEXT("APXGameModeGameplay::RestartPlayerAtPlayerStart|NewPlayer is nullptr"))
		return;
	}
	if (!StartSpot)
	{
		UE_LOG(LogActor, Warning, TEXT("APXGameModeGameplay::RestartPlayerAtPlayerStart|StartSport is nullptr"))
		return;
	}

	// Determine the class to spawn
	UClass* PlayerClassToSpawn = GetPlayerClass();

	if (!PlayerClassToSpawn)
	{
		UE_LOG(LogClass, Warning, TEXT("APXGameModeGameplay::RestartPlayerAtPlayerStart|PlayerClassToSpawn is nullptr"))
		return;
	}

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParameters.bNoFail = true;
	SpawnParameters.Owner = NewPlayer;

	PXPlayer = GetWorld()->SpawnActor<APXPlayer>(PlayerClassToSpawn, StartSpot->GetActorLocation(),
	                                             StartSpot->GetActorRotation(), SpawnParameters);

	if (!PXPlayer)
	{
		UE_LOG(LogActor, Warning, TEXT("APXGameModeGameplay::RestartPlayerAtPlayerStart|PXPlayer is nullptr"))
		return;
	}

	NewPlayer->Possess(PXPlayer);
}

void APXGameModeGameplay::HandleGameOver()
{
	FTimerHandle TimerHandle;
	constexpr float Delay{3.0f};

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &APXGameModeGameplay::OpenMenuLevel, Delay, false);
}

void APXGameModeGameplay::SpawnPuddingOnMap(const float SpawnDelay) const
{
	if (!PXSpawnItemsSubsystem)
	{
		UE_LOG(LogSubsystem, Warning, TEXT("APXGameModeGameplay::SpawnPudding|PXSpawnItemsSubsystem is nullptr"))
		return;
	}
	if (!PuddingClass)
	{
		UE_LOG(LogClass, Warning, TEXT("APXGameModeGameplay::SpawnPudding|PuddingClass is nullptr"))
		return;
	}

	PXSpawnItemsSubsystem->SpawnPudding(PuddingClass, SpawnDelay);
}

void APXGameModeGameplay::SpawnMusicSheetOnMap() const
{
	if (!PXSpawnItemsSubsystem)
	{
		UE_LOG(LogSubsystem, Warning, TEXT("APXGameModeGameplay::SpawnMusicSheet|PXSpawnItemsSubsystem is nullptr"))
		return;
	}
	if (!MusicSheetClass)
	{
		UE_LOG(LogClass, Warning, TEXT("APXGameModeGameplay::SpawnMusicSheet|MusicSheetClass is nullptr"))
		return;
	}

	PXSpawnItemsSubsystem->SpawnMusicSheet(MusicSheetClass);
}

void APXGameModeGameplay::SpawnAllFireworks() const
{
	if (!PXSpawnItemsSubsystem)
	{
		UE_LOG(LogSubsystem, Warning, TEXT("APXGameModeGameplay::SpawnAllFireworks|PXSpawnItemsSubsystem is nullptr"))
		return;
	}
	if (!FireworksClass)
	{
		UE_LOG(LogClass, Warning, TEXT("APXGameModeGameplay::SpawnAllFireworks|FireworksClass is nullptr"))
		return;
	}

	PXSpawnItemsSubsystem->SpawnAllFireworks(FireworksClass);
}

void APXGameModeGameplay::RespawnFireworks(const FVector& SpawnLocation, const float SpawnDelay) const
{
	if (!PXSpawnItemsSubsystem)
	{
		UE_LOG(LogSubsystem, Warning, TEXT("APXGameModeGameplay::RespawnFireworks|PXSpawnItemsSubsystem is nullptr"))
		return;
	}
	if (!FireworksClass)
	{
		UE_LOG(LogClass, Warning, TEXT("APXGameModeGameplay::RespawnFireworks|FireworksClass is nullptr"))
		return;
	}

	PXSpawnItemsSubsystem->RespawnFireworks(FireworksClass, SpawnDelay, SpawnLocation);
}

void APXGameModeGameplay::BindHandleGameOver()
{
	if (!PXPlayer)
	{
		UE_LOG(LogActor, Warning, TEXT("APXGameModeGameplay::BeginPlay|PXPlayer is nullptr"))
		return;
	}

	PXPlayer->OnGamerOver.AddDynamic(this, &APXGameModeGameplay::HandleGameOver);
}

void APXGameModeGameplay::OpenMenuLevel() const
{
	UGameplayStatics::OpenLevel(this, FName("Menu"));
}

TSubclassOf<APXPlayer> APXGameModeGameplay::GetPlayerClass() const
{
	const UPXGameInstance* PXGameInstance = Cast<UPXGameInstance>(GetGameInstance());

	if (!PXGameInstance)
	{
		UE_LOG(LogGameInstance, Warning, TEXT("APXGameModeGameplay::GetPlayerClass"))
		return nullptr;
	}
	if (!BoyClass)
	{
		UE_LOG(LogClass, Warning, TEXT("APXGameModeGameplay::GetPlayerClass|BoyClass is nullptr"))
		return nullptr;
	}
	if (!GirlClass)
	{
		UE_LOG(LogClass, Warning, TEXT("APXGameModeGameplay::GetPlayerClass|GirlsClass is nullptr"))
		return nullptr;
	}

	const EPlayerClass PlayerClass = PXGameInstance->GetPlayerClass();

	switch (PlayerClass)
	{
	case EPlayerClass::Boy:
		return BoyClass;
	case EPlayerClass::Girl:
		return GirlClass;
	}
	return nullptr;
}

void APXGameModeGameplay::InitializePXSpawnItemsSubsystem()
{
	PXSpawnItemsSubsystem = GetWorld()->GetSubsystem<UPXSpawnItemsSubsystem>();
}
