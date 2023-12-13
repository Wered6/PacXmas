// Copyright (c) 2023 Santa Claus. All rights reserved.


#include "PXHUD.h"
#include "Engine/Canvas.h"
#include "PacXmas/GameplayElements/Characters/Player/PXPlayer.h"

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

void APXHUD::DrawLives(const uint8_t Lives) const
{
	if (!LifeTexture)
	{
		UE_LOG(LogTexture, Warning, TEXT("APXHUD::DrawLives|LivesTexture is nullptr"))
		return;
	}

	if (bIsLifeVisible)
	{
		constexpr float LiveSize{50.f};
		// Padding between hearts
		const FVector2D LivesPadding(10.f, 10.f);

		// Create the icon from the texture
		const FCanvasIcon LiveIcon = UCanvas::MakeIcon(LifeTexture, 0, 0, LifeTexture->GetSizeX(),
		                                               LifeTexture->GetSizeY());

		for (int32 i = 0; i < Lives; ++i)
		{
			// Position for each lives icon
			const float XPos = Canvas->OrgX + (LiveSize + LivesPadding.X) * i;
			const float YPos = Canvas->OrgY + LivesPadding.Y;

			Canvas->DrawIcon(LiveIcon, XPos, YPos, LiveSize / LifeTexture->GetSizeX());
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

void APXHUD::StartHeartBlinking()
{
	constexpr float BlinkInterval{0.2f};
	BlinkCount = 0;
	GetWorld()->GetTimerManager().SetTimer(BlinkTimerHandle, this, &APXHUD::ToggleLifeVisibility, BlinkInterval,
	                                       true);
}
