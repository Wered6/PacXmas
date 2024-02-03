// Copyright (c) 2023 Smoking Carrots. All rights reserved.


#include "PXHUD.h"

#include "DigitSpriteManager/PXDigitTextureManager.h"
#include "Engine/Canvas.h"
#include "PacXmas/GameInstance/PXGameInstance.h"
#include "PacXmas/GameplayElements/Characters/Player/PXPlayer.h"
#include "PacXmas/Subsystems/ClassSubsystem/PXClassSubsystem.h"
#include "PacXmas/Subsystems/ScoreSubsystem/PXScoreSubsystem.h"
#include "PacXmas/Utilities/CustomLogs/PXCustomLogs.h"

void APXHUD::BeginPlay()
{
	Super::BeginPlay();

	BindLifeBlinking();

	InitializeDigitTextureManager();
	InitializeScoreSubsystem();
	InitializeClassSubsystem();
}

void APXHUD::DrawHUD()
{
	Super::DrawHUD();

	DrawScore();
	DrawLives();
}

void APXHUD::InitializeDigitTextureManager()
{
	if (!PXDigitTextureManagerClass)
	{
		UE_LOG(LogDigitTextureManager, Warning,
		       TEXT("APXHUD::InitializeDigitTextureManager|PXDigitTextureManagerClass is nullptr"))
		return;
	}

	PXDigitTextureManager = NewObject<UPXDigitTextureManager>(this, PXDigitTextureManagerClass);
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
	const UPXGameInstance* PXGameInstance = Cast<UPXGameInstance>(GetGameInstance());

	if (!PXGameInstance)
	{
		UE_LOG(LogGameInstance, Warning, TEXT("APXHUD::InitializeClassSubsystem|PXGameInstance is nullptr"))
		return;
	}

	PXClassSubsystem = PXGameInstance->GetSubsystem<UPXClassSubsystem>();
}

void APXHUD::DrawScore() const
{
	if (!PXScoreSubsystem)
	{
		UE_LOG(LogSubsystem, Warning, TEXT("APXHUD::DrawScore|PXScoreSubsystem is nullptr"))
		return;
	}
	if (!PXDigitTextureManager)
	{
		UE_LOG(LogDigitTextureManager, Warning, TEXT("APXHUD::DrawScore|PXDigitTextureManager is nullptr"))
		return;
	}

	const int32 CurrentScore = PXScoreSubsystem->GetScore();
	FString ScoreString = FString::FromInt(CurrentScore);

	// Set starting position of drawing digits
	FVector2D DigitPosition(Canvas->ClipX * 1.f, Canvas->ClipY * 0.01f);
	const FVector2D DigitSize(32.f, 32.f);

	for (const TCHAR Char : ScoreString)
	{
		const int32 Digit = Char - '0';
		UTexture2D* DigitTexture = PXDigitTextureManager->GetDigitTexture(Digit);

		if (!DigitTexture)
		{
			UE_LOG(LogTexture, Warning, TEXT("APXHUD::DrawScore|DigitTexture is nullptr"))
			return;
		}

		// Set correct size for texture
		const float TextureWidth = DigitTexture->GetSizeX();
		const float TextureHeight = DigitTexture->GetSizeY();
		const FVector2D Scale = FVector2D(DigitSize.X / TextureWidth, DigitSize.Y / TextureHeight);

		// Creating and drawing TileItem with digit texture
		FCanvasTileItem TileItem(DigitPosition, DigitTexture->GetResource(), FLinearColor::White);
		TileItem.Size = Scale * TextureWidth;
		TileItem.BlendMode = SE_BLEND_Translucent;
		Canvas->DrawItem(TileItem);

		DigitPosition.X += DigitSize.X;
	}
}

void APXHUD::DrawLives()
{
	const APXPlayer* PXPlayer = Cast<APXPlayer>(GetOwningPawn());

	if (!PXPlayer)
	{
		UE_LOG(LogOwner, Warning, TEXT("APXHUD::DrawLives|PXPlayer is nullptr"))
		return;
	}

	const uint8_t Lives = PXPlayer->GetLives();

	SetLifeTexture();

	if (!ChosenLifeTexture)
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
		const FCanvasIcon LifeIcon = UCanvas::MakeIcon(ChosenLifeTexture, 0, 0, ChosenLifeTexture->GetSizeX(),
		                                               ChosenLifeTexture->GetSizeY());

		for (int32 i = 0; i < Lives; ++i)
		{
			// Position for each lives icon
			const float XPos = Canvas->OrgX + (LifeSize + LivesPadding.X) * i;
			const float YPos = Canvas->OrgY + LivesPadding.Y;

			Canvas->DrawIcon(LifeIcon, XPos, YPos, LifeSize / ChosenLifeTexture->GetSizeX());
		}
	}
}

void APXHUD::SetLifeTexture()
{
	if (!PXClassSubsystem)
	{
		UE_LOG(LogSubsystem, Warning, TEXT("APXHUD::SetLifeTexture|PXClassSubsystem is nullptr"))
		return;
	}

	const EPlayerClass PlayerClass = PXClassSubsystem->GetPlayerClass();

	switch (PlayerClass)
	{
	case EPlayerClass::Boy:
		ChosenLifeTexture = LifeTextureBoy;
		break;
	case EPlayerClass::Girl:
		ChosenLifeTexture = LifeTextureGirl;
		break;
	}
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

	PXPlayer->OnCharacterHUDUpdate.AddDynamic(this, &APXHUD::StartLifeBlinking);
}
