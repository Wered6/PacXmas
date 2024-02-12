// Copyright (c) 2023 Smoking Carrots. All rights reserved.


#include "PXFireworks.h"
#include "EngineUtils.h"
#include "PacXmas/GameInstance/PXGameInstance.h"
#include "PacXmas/GameModes/Gameplay/PXGameModeGameplay.h"
#include "PacXmas/GameplayElements/Characters/Enemies/PXEnemy.h"
#include "PacXmas/GameplayElements/Characters/Player/PXPlayer.h"
#include "PacXmas/Subsystems/FlashSubsystem/PXFlashSubsystem.h"
#include "PacXmas/Subsystems/ScoreSubsystem/PXScoreSubsystem.h"
#include "PacXmas/UI/HUD/PXHUD.h"
#include "PacXmas/Utilities/CustomLogs/PXCustomLogs.h"

void APXFireworks::BeginPlay()
{
	Super::BeginPlay();

	InitializeFlashSubsystem();
	InitializeScoreSubsystem();
}

void APXFireworks::CollectItem(APXPlayer* PXPlayer)
{
	Super::CollectItem(PXPlayer);

	if (!PXFlashSubsystem)
	{
		UE_LOG(LogSubsystem, Warning, TEXT("APXFireworks::CollectItem|FlashSubsystem is nullptr"))
		return;
	}

	PXFlashSubsystem->CreateFlashEffect();
	FlashAllEnemies();
	RespawnFireworks();

	AddAndPopupScore(PXPlayer);
}

void APXFireworks::InitializeFlashSubsystem()
{
	const UPXGameInstance* PXGameInstance = Cast<UPXGameInstance>(GetGameInstance());

	if (!PXGameInstance)
	{
		UE_LOG(LogGameInstance, Warning, TEXT("APXFireworks::InitializeFlashSubsystem|PXGameInstance is nullptr"))
		return;
	}

	PXFlashSubsystem = PXGameInstance->GetSubsystem<UPXFlashSubsystem>();
}

void APXFireworks::InitializeScoreSubsystem()
{
	const UPXGameInstance* PXGameInstance = Cast<UPXGameInstance>(GetGameInstance());

	if (!PXGameInstance)
	{
		UE_LOG(LogGameInstance, Warning, TEXT("APXFireworks::InitializeScoreSubsystem|PXGameInstance is nullptr"))
		return;
	}

	PXScoreSubsystem = PXGameInstance->GetSubsystem<UPXScoreSubsystem>();
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

void APXFireworks::AddAndPopupScore(const APXPlayer* PXPlayer) const
{
	if (!PXScoreSubsystem)
	{
		UE_LOG(LogSubsystem, Warning, TEXT("APXFireworks::AddAndPopupScore|PXScoreSubsystem is nullptr"))
		return;
	}

	const APlayerController* PlayerController = Cast<APlayerController>(PXPlayer->GetController());

	if (!PlayerController)
	{
		UE_LOG(LogPlayerController, Warning, TEXT("APXFireworks::AddAndPopupScore|PlayerController is nullptr"))
		return;
	}

	APXHUD* PXHUD = Cast<APXHUD>(PlayerController->GetHUD());

	if (!PXHUD)
	{
		UE_LOG(LogHUD, Warning, TEXT("APXFireworks::AddAndPopupScore|PXHUD is nullptr"))
		return;
	}

	PXScoreSubsystem->AddScore(EScoreTypes::CollectFireworks);
	PXHUD->DisplayScorePopup(EScoreTypes::CollectFireworks);
	PXHUD->UpdateScore();
}
