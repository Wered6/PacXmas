// Copyright (c) 2023 Smoking Carrots. All rights reserved.


#include "PXHUDOverlay.h"

#include "Components/Image.h"
#include "PacXmas/DataAssets/UI/Hearts/PXHeartTexturesDA.h"
#include "PacXmas/Subsystems/ClassSubsystem/PXClassSubsystem.h"
#include "PacXmas/UI/HUD/DigitTextureManager/PXDigitTextureManager.h"
#include "PacXmas/Utilities/CustomLogs/PXCustomLogs.h"

void UPXHUDOverlay::UpdateScore(const int32 Score)
{
	InitializeDigitTextureManager();

	SetScoreInHorizontalBox(Score);
}

void UPXHUDOverlay::UpdateHearts(const uint8_t Lives, const bool bAnimate)
{
	InitializeClassSubsystem();

	SetHeartsInHorizontalBox(Lives);
	if (bAnimate)
	{
		PlayHeartsBlinkingAnimation();
	}
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

void UPXHUDOverlay::InitializeClassSubsystem()
{
	const UGameInstance* GameInstance = GetGameInstance();

	if (!GameInstance)
	{
		UE_LOG(LogGameInstance, Warning, TEXT("UPXHUDOverlay::InitializeClassSubsystem|GameInstance is nullptr"))
		return;
	}

	if (!PXClassSubsystem)
	{
		PXClassSubsystem = GameInstance->GetSubsystem<UPXClassSubsystem>();
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

void UPXHUDOverlay::SetHeartsInHorizontalBox(const uint8_t Lives)
{
	if (!HeartsHorizontalBox)
	{
		UE_LOG(LogWidget, Warning, TEXT("UPXHUDOverlay::SetHeartsInHorizontalBox|HeartsHorizontalBox is nullptr"))
		return;
	}
	if (!HeartsHorizontalBox)
	{
		UE_LOG(LogWidget, Warning, TEXT("UPXHUDOverlay::SetHeartsInHorizontalBox|HeartsHorizontalBox is nullptr"))
		return;
	}

	HeartsHorizontalBox->ClearChildren();

	UTexture2D* HeartTexture = GetHeartTexture();

	FSlateBrush Brush;
	Brush.SetResourceObject(HeartTexture);

	Brush.ImageSize = HeartSize;

	for (uint8_t i = 0; i < Lives; i++)
	{
		UImage* ImageWidget = NewObject<UImage>(this);
		ImageWidget->SetBrush(Brush);
		HeartsHorizontalBox->AddChildToHorizontalBox(ImageWidget);
	}
}

UTexture2D* UPXHUDOverlay::GetHeartTexture() const
{
	if (!PXClassSubsystem)
	{
		UE_LOG(LogSubsystem, Warning, TEXT("UPXHUDOverlay::GetHeartTexture|PXClassSubsystem is nullptr"))
		return nullptr;
	}
	if (!PXHeartTexturesDA)
	{
		UE_LOG(LogAssetData, Warning, TEXT("UPXHUDOverlay::GetHeartTexture|PXHeartTexturesDA is nullptr"))
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

void UPXHUDOverlay::PlayHeartsBlinkingAnimation()
{
	if (!HeartsBlinking)
	{
		UE_LOG(LogAnimation, Warning, TEXT("UPXHUDOverlay::PlayHeartsBlinkingAnimation|HeartsBlinking is nullptr"))
		return;
	}

	PlayAnimation(HeartsBlinking);
}
