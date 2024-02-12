// Copyright (c) 2023 Smoking Carrots. All rights reserved.


#include "PXHUD.h"
#include "Blueprint/UserWidget.h"
#include "HUDOverlay/PXHUDOverlay.h"
#include "PacXmas/GameInstance/PXGameInstance.h"
#include "PacXmas/GameplayElements/Characters/Player/PXPlayer.h"
#include "PacXmas/Subsystems/ScoreSubsystem/PXScoreSubsystem.h"
#include "PacXmas/Utilities/CustomLogs/PXCustomLogs.h"
#include "ScorePupup/PXScorePopup.h"

void APXHUD::BeginPlay()
{
	Super::BeginPlay();

	BindUpdateHearts();

	InitializeScoreSubsystem();

	InitializeHUDOverlayWidget();
	AddHUDOverlayToTheViewport();

	UpdateScore();
	SetHeartsAtBeginning();
}

void APXHUD::UpdateScore() const
{
	if (!PXHUDOverlay)
	{
		UE_LOG(LogWidget, Warning, TEXT("APXHUD::UpdateScore|PXHUDOverlay is nullptr"))
		return;
	}
	if (!PXScoreSubsystem)
	{
		UE_LOG(LogSubsystem, Warning, TEXT("APXHUD::UpdateScore|PXScoreSubsystem is nullptr"))
		return;
	}

	const int32 Score = PXScoreSubsystem->GetScore();

	PXHUDOverlay->UpdateScore(Score);
}

void APXHUD::SetHeartsAtBeginning() const
{
	if (!PXHUDOverlay)
	{
		UE_LOG(LogWidget, Warning, TEXT("APXHUD::SetHeartsAtBeginning|PXHUDOverlay is nullptr"))
		return;
	}

	const uint8_t Lives = GetLives();

	PXHUDOverlay->UpdateHearts(Lives, false);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void APXHUD::UpdateHearts()
{
	if (!PXHUDOverlay)
	{
		UE_LOG(LogWidget, Warning, TEXT("APXHUD::UpdateHearts|PXHUDOverlay is nullptr"))
		return;
	}

	const uint8_t Lives = GetLives();

	PXHUDOverlay->UpdateHearts(Lives, true);
}

void APXHUD::DisplayScorePopup(const EScoreTypes ScoreType)
{
	InitializeScorePopupWidget();

	if (!PXScoreSubsystem)
	{
		UE_LOG(LogManager, Warning, TEXT("APXHUD::DisplayScorePopup|PXScoreSubsystem is nullptr"))
		return;
	}
	if (!PXScorePopup)
	{
		UE_LOG(LogWidget, Warning, TEXT("APXHUD::DisplayScorePopup|PXScorePopup is nullptr"))
		return;
	}

	const int32 Score = PXScoreSubsystem->GetScoreBasedOnType(ScoreType);
	const APlayerController* PlayerController = GetOwningPlayerController();

	PXScorePopup->Play(Score, PlayerController);
}

void APXHUD::InitializeHUDOverlayWidget()
{
	if (!PXHUDOverlayClass)
	{
		UE_LOG(LogClass, Warning, TEXT("APXHUD::InitializeHUDOverlayWidget|PXHUDOverlayClass is nullptr"))
		return;
	}

	PXHUDOverlay = CreateWidget<UPXHUDOverlay>(GetWorld(), PXHUDOverlayClass);
}

void APXHUD::InitializeScorePopupWidget()
{
	if (!PXScorePopupClass)
	{
		UE_LOG(LogClass, Warning, TEXT("APXHUD::InitializeScorePopupWidget|PXScorePopupClass is nullptr"))
		return;
	}

	PXScorePopup = CreateWidget<UPXScorePopup>(GetWorld(), PXScorePopupClass);
}

void APXHUD::InitializeScoreSubsystem()
{
	const UPXGameInstance* PXGameInstance = Cast<UPXGameInstance>(GetGameInstance());

	if (!PXGameInstance)
	{
		UE_LOG(LogGameInstance, Warning, TEXT("APXHUD::InitializeScoreSubsystem|PXGameInstance is nullptr"))
		return;
	}

	PXScoreSubsystem = PXGameInstance->GetSubsystem<UPXScoreSubsystem>();
}


void APXHUD::AddHUDOverlayToTheViewport() const
{
	if (!PXHUDOverlay)
	{
		UE_LOG(LogWidget, Warning, TEXT("APXHUD::AddHUDOverlayToTheViewport|PXHUDOverlay is nullptr"))
		return;
	}

	PXHUDOverlay->AddToViewport();
}

uint8_t APXHUD::GetLives() const
{
	const APXPlayer* PXPlayer = Cast<APXPlayer>(GetOwningPawn());

	if (!PXPlayer)
	{
		UE_LOG(LogOwner, Warning, TEXT("APXHUD::GetLives|PXPlayer is nullptr"))
		return 0;
	}

	return PXPlayer->GetLives();
}

void APXHUD::BindUpdateHearts()
{
	APXPlayer* PXPlayer = Cast<APXPlayer>(GetOwningPawn());

	if (!PXPlayer)
	{
		UE_LOG(LogOwner, Warning, TEXT("APXHUD::BindUpdateHearts|PXPlayer is nullptr"))
		return;
	}

	PXPlayer->OnPlayerHUDUpdate.AddDynamic(this, &APXHUD::UpdateHearts);
}
