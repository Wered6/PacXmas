// Copyright (c) 2023 Santa Claus. All rights reserved.


#include "PXHUD.h"
#include "Engine/Canvas.h"
#include "PacXmas/GameInstance/PXGameInstance.h"
#include "PacXmas/GameplayElements/Characters/Player/PXPlayer.h"
#include "PacXmas/Utilities/CustomLogs/PXCustomLogs.h"

void APXHUD::DrawHUD()
{
	Super::DrawHUD();

	const APXPlayer* PlayerCharacter = Cast<APXPlayer>(GetOwningPawn());

	if (!PlayerCharacter)
	{
		UE_LOG(LogActor, Warning, TEXT("APXHUD::DrawHUD|PlayerCharacter is nullptr"))
		return;
	}

	DrawLives(PlayerCharacter->GetLives());
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
