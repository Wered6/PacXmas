// Copyright (c) 2023 Smoking Carrots. All rights reserved.


#include "PXScorePopup.h"
#include "Animation/WidgetAnimation.h"
#include "Components/HorizontalBox.h"
#include "Components/Image.h"
#include "Kismet/GameplayStatics.h"
#include "PacXmas/DataAssets/UI/Digits/PXDigitTexturesDA.h"
#include "PacXmas/Utilities/CustomLogs/PXCustomLogs.h"

void UPXScorePopup::SetScore(const int32 Score)
{
	if (Score >= 0)
	{
		AddSignTexture(true);
	}
	else
	{
		AddSignTexture(false);
	}

	AddDigitsTextures(Score);
}

void UPXScorePopup::SetPositionInViewport(const APlayerController* PlayerController)
{
	if (!PlayerController)
	{
		UE_LOG(LogController, Warning, TEXT("UPXScorePopup::SetPositionInViewport|PlayerController is nullptr"))
		return;
	}

	const APawn* Pawn = PlayerController->GetPawn();

	if (!Pawn)
	{
		UE_LOG(LogActor, Warning, TEXT("UPXScorePopup::SetPositionInViewport|Pawn is nullptr"))
		return;
	}

	const FVector PawnLocation = Pawn->GetActorLocation();
	FVector2D ScreenPosition;
	UGameplayStatics::ProjectWorldToScreen(PlayerController, PawnLocation, ScreenPosition);

	Super::SetPositionInViewport(ScreenPosition);
}

void UPXScorePopup::PlayFadingUpAnimation()
{
	if (!FadingUp)
	{
		UE_LOG(LogAnimation, Warning, TEXT("UPXScorePopup::PlayAnimation|FadingUp is nullptr"))
		return;
	}

	PlayAnimation(FadingUp);

	SetTimerRemoveFromParent();
}

void UPXScorePopup::AddSignTexture(const bool bPositive)
{
	if (!PXDigitTexturesDA)
	{
		UE_LOG(LogAssetData, Warning, TEXT("UPXScorePopup::AddSignTexture|PXDigitTexturesDA is nullptr"))
		return;
	}

	UTexture2D* SignTexture = PXDigitTexturesDA->GetSignTexture(bPositive);

	AddChildToHorizontalBox(SignTexture);
}

void UPXScorePopup::AddDigitsTextures(const int32 Score)
{
	if (!PXDigitTexturesDA)
	{
		UE_LOG(LogAssetData, Warning, TEXT("UPXScorePopup::AddDigitsTextures|PXDigitTexturesDA is nullptr"))
		return;
	}

	TArray<int32> DigitsArray = ConvertScoreIntoArray(Score);

	// Add all digits into horizontal box
	for (const int32 Digit : DigitsArray)
	{
		UTexture2D* DigitTexture = PXDigitTexturesDA->GetDigitTexture(Digit);

		AddChildToHorizontalBox(DigitTexture);
	}
}

TArray<int32> UPXScorePopup::ConvertScoreIntoArray(const int32 Score) const
{
	// Get rid of sign
	TArray<int32> DigitArray;
	int32 AbsoluteScore = FMath::Abs(Score);

	// Transfer digits into array
	while (AbsoluteScore > 0)
	{
		int32 Digit = AbsoluteScore % 10;
		DigitArray.Insert(Digit, 0);
		AbsoluteScore /= 10;
	}
	// If the original number was 0, add a single 0 digit
	if (DigitArray.Num() == 0)
	{
		DigitArray.Add(0);
	}

	return DigitArray;
}

void UPXScorePopup::AddChildToHorizontalBox(UTexture2D* Texture)
{
	if (!ScoreHorizontalBox)
	{
		UE_LOG(LogWidget, Warning, TEXT("UPXScorePopup::AddChildToHorizontalBox|ScoreHorizontalBox is nullptr"))
		return;
	}

	// Set up the brush with the digit texture
	FSlateBrush Brush;
	Brush.SetResourceObject(Texture);

	// Resizing
	Brush.ImageSize = CharSize;

	// Create the UImage widget
	UImage* ImageWidget = NewObject<UImage>(this);
	ImageWidget->SetBrush(Brush);

	// Add the image widget to the horizontal box
	ScoreHorizontalBox->AddChildToHorizontalBox(ImageWidget);
}

void UPXScorePopup::SetTimerRemoveFromParent()
{
	// Set a timer to remove the widget after animation has finished
	const float AnimationDuration = FadingUp->GetEndTime() - FadingUp->GetStartTime();

	FTimerHandle TimerHandle;
	const FTimerDelegate TimerDelegate = FTimerDelegate::CreateUObject(this, &UPXScorePopup::RemoveFromParent);
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, AnimationDuration, false);
}
