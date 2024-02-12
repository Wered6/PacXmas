// Copyright (c) 2023 Smoking Carrots. All rights reserved.


#include "PXHUDOverlay.h"
#include "PacXmas/UI/HUD/DigitTextureManager/PXDigitTextureManager.h"
#include "PacXmas/Utilities/CustomLogs/PXCustomLogs.h"

void UPXHUDOverlay::UpdateScore(const int32 Score)
{
	InitializeDigitTextureManager();

	SetScoreInHorizontalBox(Score);
}

void UPXHUDOverlay::InitializeDigitTextureManager()
{
	if (!PXDigitTextureManagerClass)
	{
		UE_LOG(LogClass, Warning,
		       TEXT("UPXHUDOverlay::InitializeDigitTextureManager|PXDigitTextureManagerClass is nullptr"))
		return;
	}

	if (!PXDigitTextureManager)
	{
		PXDigitTextureManager = NewObject<UPXDigitTextureManager>(this, PXDigitTextureManagerClass);
	}
}

void UPXHUDOverlay::SetScoreInHorizontalBox(const int32 Score) const
{
	if (!PXDigitTextureManager)
	{
		UE_LOG(LogManager, Warning, TEXT("UPXHUDOverlay::SetScoreInHorizontalBox|PXDigitTextureManager is nullptr"))
		return;
	}
	if (!ScoreHorizontalBox)
	{
		UE_LOG(LogWidget, Warning, TEXT("UPXHUDOverlay::SetScoreInHorizontalBox|ScoreHorizontalBox is nullptr"))
		return;
	}

	ScoreHorizontalBox->ClearChildren();
	
	PXDigitTextureManager->SetScoreInHorizontalBox(ScoreHorizontalBox, Score, CharSize, false);
}
