// Copyright (c) 2023 Smoking Carrots. All rights reserved.


#include "PXFireworks.h"
#include "EngineUtils.h"
#include "PacXmas/GameModes/Gameplay/PXGameModeGameplay.h"
#include "PacXmas/GameplayElements/Characters/Enemies/PXEnemy.h"
#include "PacXmas/Subsystems/FlashSubsystem/PXFlashSubsystem.h"
#include "PacXmas/Subsystems/ScoreSubsystem/PXScoreSubsystem.h"
#include "PacXmas/Utilities/CustomLogs/PXCustomLogs.h"

void APXFireworks::BeginPlay()
{
	Super::BeginPlay();

	const UGameInstance* GameInstance = GetGameInstance();
	if (!GameInstance)
	{
		UE_LOG(LogGameInstance, Warning, TEXT("APXFireworks::BeginPlay|GameInstance is nullptr"))
		return;
	}

	PXFlashSubsystem = GameInstance->GetSubsystem<UPXFlashSubsystem>();

	PXScoreSubsystem = GameInstance->GetSubsystem<UPXScoreSubsystem>();
}

void APXFireworks::CollectItem(APXPlayer* PlayerCharacter)
{
	Super::CollectItem(PlayerCharacter);

	if (!PXFlashSubsystem)
	{
		UE_LOG(LogSubsystem, Warning, TEXT("APXFireworks::CollectItem|FlashSubsystem is nullptr"))
		return;
	}

	PXFlashSubsystem->CreateFlashEffect();
	FlashAllEnemies();
	RespawnFireworks();

	PXScoreSubsystem->AddScore(EScoreTypes::CollectFireworks);
}

void APXFireworks::FlashAllEnemies() const
{
	for (TActorIterator<APXEnemy> It(GetWorld()); It; ++It)
	{
		APXEnemy* PXEnemy = *It;
		if (IsValid(PXEnemy))
		{
			PXEnemy->GetFlashed();
		}
	}
}

void APXFireworks::RespawnFireworks() const
{
	const APXGameModeGameplay* PXGameModeGameplay = GetWorld()->GetAuthGameMode<APXGameModeGameplay>();

	if (!PXGameModeGameplay)
	{
		UE_LOG(LogGameMode, Warning, TEXT("APXFireworks::RespawnFireworks|PXGameModeGameplay is nullptr"))
		return;
	}

	const FVector SpawnLocation = GetActorLocation();
	constexpr float SpawnDelay{25.f};

	PXGameModeGameplay->RespawnFireworks(SpawnLocation, SpawnDelay);
}
