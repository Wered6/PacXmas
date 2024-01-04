// Copyright (c) 2023 Santa Claus. All rights reserved.


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

	APawn* ControlledPawn = GetPawn();

	if (!ControlledPawn)
	{
		UE_LOG(LogPlayerController, Warning, TEXT("APXPlayerControllerGameplay::BeginPlay|ControlledPawn is nullptr"));
		return;
	}

	PXPlayer = Cast<APXPlayer>(ControlledPawn);
}

void APXPlayerControllerGameplay::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (!InputComponent)
	{
		UE_LOG(LogComponent, Warning,
		       TEXT("APXPlayerControllerGameplay::SetupInputComponent|InputComponent is nullptr"))
		return;
	}

	InputComponent->BindAxis(TEXT("MovePlayerHorizontal"), this, &APXPlayerControllerGameplay::MovePlayerHorizontal);
	InputComponent->BindAxis(TEXT("MovePlayerVertical"), this, &APXPlayerControllerGameplay::MovePlayerVertical);

	InputComponent->BindAction(TEXT("ShootPudding"), IE_Pressed, this,
	                           &APXPlayerControllerGameplay::OnShootPuddingPressed);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void APXPlayerControllerGameplay::MovePlayerHorizontal(const float Value)
{
	if (!PXPlayer)
	{
		UE_LOG(LogPlayerController, Warning,
		       TEXT("APXPlayerControllerGameplay::MovePlayerHorizontal|MyPlayer is nullptr"));
		return;
	}

	PXPlayer->MoveHorizontal(Value);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void APXPlayerControllerGameplay::MovePlayerVertical(const float Value)
{
	if (!PXPlayer)
	{
		UE_LOG(LogPlayerController, Warning,
		       TEXT("APXPlayerControllerGameplay::MovePlayerVertical|MyPlayer is nullptr"));
		return;
	}

	PXPlayer->MoveVertical(Value);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void APXPlayerControllerGameplay::OnShootPuddingPressed()
{
	if (!PXPlayer)
	{
		UE_LOG(LogPlayerController, Warning,
		       TEXT("APXPlayerControllerGameplay::OnShootPuddingPressed|MyPlayer is nullptr"))
		return;
	}

	PXPlayer->ShootPudding();
}
