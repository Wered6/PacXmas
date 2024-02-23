// Copyright (c) 2023 Smoking Carrots. All rights reserved.


#include "PXPlayerControllerGameplay.h"
#include "PacXmas/GameplayElements/Characters/Player/PXPlayer.h"
#include "PacXmas/Utilities/CustomLogs/PXCustomLogs.h"

APXPlayerControllerGameplay::APXPlayerControllerGameplay()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APXPlayerControllerGameplay::BeginPlay()
{
	Super::BeginPlay();

	InitializePlayer();
}

void APXPlayerControllerGameplay::SetPlayerEnabledState(const bool bPlayerEnabled)
{
	if (bPlayerEnabled)
	{
		EnableInput(this);
	}
	else
	{
		DisableInput(this);
	}
}

void APXPlayerControllerGameplay::InitializePlayer()
{
	APawn* ControlledPawn = GetPawn();

	if (!ControlledPawn)
	{
		UE_LOG(LogPlayerController, Warning,
		       TEXT("APXPlayerControllerGameplay::InitializePlayer|ControlledPawn is nullptr"));
		return;
	}

	PXPlayer = Cast<APXPlayer>(ControlledPawn);
}

void APXPlayerControllerGameplay::MovePlayer(const FVector& Value)
{
	if (!PXPlayer)
	{
		UE_LOG(LogPlayer, Warning, TEXT("APXPlayerControllerGameplay::MovePlayer|PXPlayer is nullptr"))
		return;
	}

	PXPlayer->Move(Value);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void APXPlayerControllerGameplay::OnShootPuddingPressed()
{
	if (!PXPlayer)
	{
		UE_LOG(LogPlayerController, Warning,
		       TEXT("APXPlayerControllerGameplay::OnShootPuddingPressed|PXPlayer is nullptr"))
		return;
	}

	PXPlayer->ShootPudding();
}
