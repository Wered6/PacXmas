// Copyright (c) 2023 Smoking Carrots. All rights reserved.


#include "PXGameModeGameplay.h"

#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"
#include "PacXmas/DataAssets/Classes/Items/PXItemClassesDA.h"
#include "PacXmas/DataAssets/Classes/Player/PXPlayerClassesDA.h"
#include "PacXmas/GameInstance/PXGameInstance.h"
#include "PacXmas/GameplayElements/Characters/Enemies/PXEnemy.h"
#include "PacXmas/GameplayElements/Characters/Player/PXPlayer.h"
#include "PacXmas/GameplayElements/Items/Fireworks/PXFireworks.h"
#include "PacXmas/GameplayElements/Items/MusicSheet/PXMusicSheet.h"
#include "PacXmas/GameplayElements/Items/Pudding/PXPudding.h"
#include "PacXmas/PlayerControllers/Gameplay/PXPlayerControllerGameplay.h"
#include "PacXmas/Subsystems/ClassSubsystem/PXClassSubsystem.h"
#include "PacXmas/Subsystems/SpawnItemsSubsystem/PXSpawnItemsSubsystem.h"
#include "PacXmas/Utilities/CustomLogs/PXCustomLogs.h"

void APXGameModeGameplay::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	InitializeClassSubsystem();
	InitializeSpawnItemsSubsystem();
}

void APXGameModeGameplay::BeginPlay()
{
	Super::BeginPlay();

	BindHandleGameOver();

	HandleGameStart();
}

void APXGameModeGameplay::RestartPlayerAtPlayerStart(AController* NewPlayer, AActor* StartSpot)
{
	if (!PXClassSubsystem)
	{
		UE_LOG(LogSubsystem, Warning,
		       TEXT("APXGameModeGameplay::RestartPlayerAtPlayerStart|PXClassSubsystem is nullptr"))
		return;
	}
	if (!PXPlayerClassesDA)
	{
		UE_LOG(LogAssetData, Warning,
		       TEXT("APXGameModeGameplay::RestartPlayerAtPlayerStart|PXPlayerClassesDA is nullptr"))
		return;
	}
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
	const EPlayerClass PlayerClass = PXClassSubsystem->GetPlayerClass();
	UClass* PlayerClassToSpawn = PXPlayerClassesDA->GetPlayerClass(PlayerClass);

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
	if (!PXItemClassesDA)
	{
		UE_LOG(LogAssetData, Warning, TEXT("APXGameModeGameplay::SpawnPuddingOnMap|PXItemClassesDA is nullptr"))
		return;
	}

	const TSubclassOf<APXPudding> PuddingClass = PXItemClassesDA->GetPuddingClass();

	PXSpawnItemsSubsystem->SpawnPudding(PuddingClass, SpawnDelay);
}

void APXGameModeGameplay::SpawnMusicSheetOnMap() const
{
	if (!PXSpawnItemsSubsystem)
	{
		UE_LOG(LogSubsystem, Warning, TEXT("APXGameModeGameplay::SpawnMusicSheet|PXSpawnItemsSubsystem is nullptr"))
		return;
	}
	if (!PXItemClassesDA)
	{
		UE_LOG(LogAssetData, Warning, TEXT("APXGameModeGameplay::SpawnMusicSheetOnMap|PXItemClassesDA is nullptr"))
		return;
	}

	const TSubclassOf<APXMusicSheet> MusicSheetClass = PXItemClassesDA->GetMusicSheetClass();

	PXSpawnItemsSubsystem->SpawnMusicSheet(MusicSheetClass);
}

void APXGameModeGameplay::SpawnAllFireworks() const
{
	if (!PXSpawnItemsSubsystem)
	{
		UE_LOG(LogSubsystem, Warning, TEXT("APXGameModeGameplay::SpawnAllFireworks|PXSpawnItemsSubsystem is nullptr"))
		return;
	}
	if (!PXItemClassesDA)
	{
		UE_LOG(LogAssetData, Warning, TEXT("APXGameModeGameplay::SpawnAllFireworks|PXItemClassesDA is nullptr"))
		return;
	}

	const TSubclassOf<APXFireworks> FireworksClass = PXItemClassesDA->GetFireworksClass();

	PXSpawnItemsSubsystem->SpawnAllFireworks(FireworksClass);
}

void APXGameModeGameplay::RespawnFireworks(const FVector& SpawnLocation, const float SpawnDelay) const
{
	if (!PXSpawnItemsSubsystem)
	{
		UE_LOG(LogSubsystem, Warning, TEXT("APXGameModeGameplay::RespawnFireworks|PXSpawnItemsSubsystem is nullptr"))
		return;
	}
	if (!PXItemClassesDA)
	{
		UE_LOG(LogAssetData, Warning, TEXT("APXGameModeGameplay::RespawnFireworks|PXItemClassesDA is nullptr"))
		return;
	}

	const TSubclassOf<APXFireworks> FireworksClass = PXItemClassesDA->GetFireworksClass();

	PXSpawnItemsSubsystem->RespawnFireworks(FireworksClass, SpawnDelay, SpawnLocation);
}

void APXGameModeGameplay::InitializeClassSubsystem()
{
	const UPXGameInstance* PXGameInstance = Cast<UPXGameInstance>(GetGameInstance());

	if (!PXGameInstance)
	{
		UE_LOG(LogGameInstance, Warning,
		       TEXT("APXGameModeGameplay::InitializeClassSubsystem|PXGameInstance is nullptr"))
		return;
	}

	PXClassSubsystem = PXGameInstance->GetSubsystem<UPXClassSubsystem>();
}

void APXGameModeGameplay::BindHandleGameOver()
{
	if (!PXPlayer)
	{
		UE_LOG(LogActor, Warning, TEXT("APXGameModeGameplay::BindHandleGameOver|PXPlayer is nullptr"))
		return;
	}

	PXPlayer->OnGameOver.AddDynamic(this, &APXGameModeGameplay::HandleGameOver);
}

void APXGameModeGameplay::OpenMenuLevel() const
{
	UGameplayStatics::OpenLevel(this, FName("Menu"));
}

void APXGameModeGameplay::InitializeSpawnItemsSubsystem()
{
	PXSpawnItemsSubsystem = GetWorld()->GetSubsystem<UPXSpawnItemsSubsystem>();
}

void APXGameModeGameplay::HandleGameStart()
{
	SpawnPuddingOnMap();
	SpawnMusicSheetOnMap();
	SpawnAllFireworks();

	PrintCountDown();
	DelayPlayer();
	DelayEnemies();
}

void APXGameModeGameplay::DelayPlayer()
{
	APXPlayerControllerGameplay* PXPlayerControllerGameplay = Cast<APXPlayerControllerGameplay>(
		GetWorld()->GetFirstPlayerController());

	if (!PXPlayerControllerGameplay)
	{
		UE_LOG(LogController, Warning,
		       TEXT("APXGameModeGameplay::HandleGameStart|PXPlayerControllerGameplay is nullptr"))
		return;
	}

	// Disable player's input
	PXPlayerControllerGameplay->SetPlayerEnabledState(false);

	// Set timer to enable player's input in 3sec
	FTimerHandle PlayerEnableTimerHandle;
	const FTimerDelegate PlayerEnableTimerDelegate = FTimerDelegate::CreateUObject(
		PXPlayerControllerGameplay,
		&APXPlayerControllerGameplay::SetPlayerEnabledState,
		true
	);
	GetWorldTimerManager().SetTimer(
		PlayerEnableTimerHandle,
		PlayerEnableTimerDelegate,
		StartDelay,
		false
	);
}

void APXGameModeGameplay::DelayEnemies()
{
	for (TActorIterator<APXEnemy> It(GetWorld(), APXEnemy::StaticClass()); It; ++It)
	{
		const APXEnemy* PXEnemy = *It;

		DelayEnemy(PXEnemy);
	}
}

void APXGameModeGameplay::DelayEnemy(const APXEnemy* PXEnemy)
{
	if (!PXEnemy)
	{
		UE_LOG(LogClass, Warning, TEXT("APXGameModeGameplay::DelayEnemy|PXEnemy is nullptr"))
		return;
	}

	// Disable enemy's movement
	PXEnemy->SetCanMove(false);

	// Set timer to enable enemy's movement in 3sec
	FTimerHandle EnemyCanMoveTimerHandle;
	const FTimerDelegate EnemyCanMoveTimerDelegate = FTimerDelegate::CreateUObject(
		PXEnemy,
		&APXEnemy::SetCanMove,
		true
	);
	GetWorldTimerManager().SetTimer(
		EnemyCanMoveTimerHandle,
		EnemyCanMoveTimerDelegate,
		StartDelay,
		false
	);
}
