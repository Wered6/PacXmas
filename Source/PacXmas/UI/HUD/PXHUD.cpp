// Copyright (c) 2023 Smoking Carrots. All rights reserved.


#include "PXHUD.h"
#include "Blueprint/UserWidget.h"
#include "Engine/Canvas.h"
#include "HUDOverlay/PXHUDOverlay.h"
#include "PacXmas/DataAssets/UI/Hearts/PXHeartTexturesDA.h"
#include "PacXmas/GameInstance/PXGameInstance.h"
#include "PacXmas/GameplayElements/Characters/Player/PXPlayer.h"
#include "PacXmas/Subsystems/ClassSubsystem/PXClassSubsystem.h"
#include "PacXmas/Subsystems/ScoreSubsystem/PXScoreSubsystem.h"
#include "PacXmas/Utilities/CustomLogs/PXCustomLogs.h"
#include "ScorePupup/PXScorePopup.h"

void APXHUD::BeginPlay()
{
	Super::BeginPlay();

	BindLifeBlinking();

	InitializeScoreSubsystem();
	InitializeClassSubsystem();

	InitializeHUDOverlayWidget();
	AddHUDOverlayToTheViewport();
	UpdateScore();
}

void APXHUD::DrawHUD()
{
	Super::DrawHUD();

	DrawLives();
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

void APXHUD::InitializeClassSubsystem()
{
	const UGameInstance* GameInstance = GetGameInstance();

	if (!GameInstance)
	{
		UE_LOG(LogGameInstance, Warning, TEXT("APXHUD::InitializeClassSubsystem|GameInstance is nullptr"))
		return;
	}

	PXClassSubsystem = GameInstance->GetSubsystem<UPXClassSubsystem>();
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

void APXHUD::DrawLives() const
{
	const uint8_t Lives = GetLives();
	UTexture2D* LifeTexture = GetHeartTexture();

	if (!LifeTexture)
	{
		UE_LOG(LogTexture, Warning, TEXT("APXHUD::DrawLives|LivesTexture is nullptr"))
		return;
	}

	if (bIsLifeVisible)
	{
		constexpr float LifeSize{50.f};
		// Padding between hearts
		const FVector2D LivesPadding(10.f, 10.f);

		// Create the icon from the texture
		const FCanvasIcon LifeIcon = UCanvas::MakeIcon(LifeTexture, 0, 0, LifeTexture->GetSizeX(),
		                                               LifeTexture->GetSizeY());

		for (int32 i = 0; i < Lives; ++i)
		{
			// Position for each lives icon
			const float XPos = Canvas->OrgX + (LifeSize + LivesPadding.X) * i;
			const float YPos = Canvas->OrgY + LivesPadding.Y;

			Canvas->DrawIcon(LifeIcon, XPos, YPos, LifeSize / LifeTexture->GetSizeX());
		}
	}
}

UTexture2D* APXHUD::GetHeartTexture() const
{
	if (!PXHeartTexturesDA)
	{
		UE_LOG(LogAssetData, Warning, TEXT("APXHUD::GetLifeTexture|PXHeartTexturesDA is nullptr"))
		return nullptr;
	}
	if (!PXClassSubsystem)
	{
		UE_LOG(LogSubsystem, Warning, TEXT("APXHUD::GetHeartTexture|PXClassSubsystem is nullptr"))
		return nullptr;
	}

	const EPlayerClass PlayerClass = PXClassSubsystem->GetPlayerClass();

	switch (PlayerClass)
	{
	case EPlayerClass::Girl:
		{
			return PXHeartTexturesDA->GetHeartTextureGirl();
		}
	case EPlayerClass::Boy:
		{
			return PXHeartTexturesDA->GetHeartTextureBoy();
		}
	default:
		{
			return nullptr;
		}
	}
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

void APXHUD::ToggleLifeVisibility()
{
	bIsLifeVisible = !bIsLifeVisible;
	BlinkCount++;

	if (BlinkCount >= MaxBlinkCount)
	{
		GetWorld()->GetTimerManager().ClearTimer(BlinkTimerHandle);
		bIsLifeVisible = true; // Ensure it's visible after the last blink
		BlinkCount = 0;
	}
}

void APXHUD::StartLifeBlinking()
{
	constexpr float BlinkInterval{0.2f};
	BlinkCount = 0;
	GetWorld()->GetTimerManager().SetTimer(BlinkTimerHandle, this, &APXHUD::ToggleLifeVisibility, BlinkInterval,
	                                       true);
}

void APXHUD::BindLifeBlinking()
{
	APXPlayer* PXPlayer = Cast<APXPlayer>(GetOwningPawn());

	if (!PXPlayer)
	{
		UE_LOG(LogOwner, Warning, TEXT("APXHUD::BindHeartBlinking|PXPlayer is nullptr"))
		return;
	}

	PXPlayer->OnPlayerHUDUpdate.AddDynamic(this, &APXHUD::StartLifeBlinking);
}
