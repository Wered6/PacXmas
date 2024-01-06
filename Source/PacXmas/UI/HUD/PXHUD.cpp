// Copyright (c) 2023 Smoking Carrots. All rights reserved.


#include "PXHUD.h"
#include "Engine/Canvas.h"
#include "PacXmas/GameInstance/PXGameInstance.h"
#include "PacXmas/GameplayElements/Characters/Player/PXPlayer.h"
#include "PacXmas/Subsystems/ScoreSubsystem/PXScoreSubsystem.h"
#include "PacXmas/Utilities/CustomLogs/PXCustomLogs.h"

void APXHUD::BeginPlay()
{
	Super::BeginPlay();

	APXPlayer* PXPlayer = Cast<APXPlayer>(GetOwningPawn());

	if (!PXPlayer)
	{
		UE_LOG(LogOwner, Warning, TEXT("APXHUD::APXHUD|PXPlayer is nullptr"))
		return;
	}

	PXPlayer->OnCharacterHUDUpdate.AddDynamic(this, &APXHUD::StartHeartBlinking);

	PXScoreSubsystem = GetGameInstance()->GetSubsystem<UPXScoreSubsystem>();
}

void APXHUD::DrawHUD()
{
	Super::DrawHUD();

	const APXPlayer* PXPlayer = Cast<APXPlayer>(GetOwningPawn());

	if (!PXPlayer)
	{
		UE_LOG(LogOwner, Warning, TEXT("APXHUD::DrawHUD|PXPlayer is nullptr"))
		return;
	}

	DrawLives(PXPlayer->GetLives());
	DrawScore();
}

void APXHUD::DrawScore() const
{
	if (!PXScoreSubsystem)
	{
		UE_LOG(LogSubsystem, Warning, TEXT("APXHUD::DrawScore|PXScoreSubsystem is nullptr"))
		return;
	}

	// Get the current score
	const int32 CurrentScore = PXScoreSubsystem->GetScore();

	// Set up the position and size for the score text
	const FVector2d ScorePosition(Canvas->ClipX * 0.95f, 20.f);
	const FVector2d ScoreSize(200.f, 100.f);
	const FText ScoreText = FText::FromString(FString::Printf(TEXT("Score: %d"), CurrentScore));

	// Draw the score text
	FCanvasTextItem TextItem(ScorePosition, ScoreText, GEngine->GetMediumFont(), FLinearColor::White);
	TextItem.Scale = ScoreSize / 100.f;
	Canvas->DrawItem(TextItem);
}

void APXHUD::DrawLives(const uint8_t Lives)
{
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

void APXHUD::SetLifeTexture()
{
	const UPXGameInstance* PXGameInstance = Cast<UPXGameInstance>(GetGameInstance());

	if (!PXGameInstance)
	{
		UE_LOG(LogGameInstance, Warning, TEXT("APXHUD::SetLifeTexture|PXGameInstance is nullptr"))
		return;
	}

	const EPlayerClass PlayerClass = PXGameInstance->GetPlayerClass();

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

void APXHUD::StartHeartBlinking()
{
	constexpr float BlinkInterval{0.2f};
	BlinkCount = 0;
	GetWorld()->GetTimerManager().SetTimer(BlinkTimerHandle, this, &APXHUD::ToggleLifeVisibility, BlinkInterval,
	                                       true);
}
