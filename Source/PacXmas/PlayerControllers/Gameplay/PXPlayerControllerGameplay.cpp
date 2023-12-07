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

	MyPlayer = Cast<APXPlayer>(ControlledPawn);
}

void APXPlayerControllerGameplay::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
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

void APXPlayerControllerGameplay::MovePlayerHorizontal(const float Value)
{
	if (!MyPlayer)
	{
		UE_LOG(LogPlayerController, Warning,
		       TEXT("APXPlayerControllerGameplay::MovePlayerHorizontal|MyPlayer is nullptr"));
		return;
	}

	MyPlayer->MoveHorizontal(Value);
}

void APXPlayerControllerGameplay::MovePlayerVertical(const float Value)
{
	if (!MyPlayer)
	{
		UE_LOG(LogPlayerController, Warning,
		       TEXT("APXPlayerControllerGameplay::MovePlayerVertical|MyPlayer is nullptr"));
		return;
	}

	MyPlayer->MoveVertical(Value);
}

void APXPlayerControllerGameplay::OnShootPuddingPressed()
{
	if (!MyPlayer)
	{
		UE_LOG(LogPlayerController, Warning,
		       TEXT("APXPlayerControllerGameplay::OnShootPuddingPressed|MyPlayer is nullptr"))
		return;
	}

	MyPlayer->ShootPudding();
}
