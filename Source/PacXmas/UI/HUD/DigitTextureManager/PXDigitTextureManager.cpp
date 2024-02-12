// Copyright (c) 2023 Smoking Carrots. All rights reserved.


#include "PXDigitTextureManager.h"
#include "Components/Image.h"
#include "PacXmas/DataAssets/UI/Digits/PXDigitTexturesDA.h"
#include "PacXmas/Utilities/CustomLogs/PXCustomLogs.h"

void UPXDigitTextureManager::SetScoreInHorizontalBox(UHorizontalBox* ScoreHorizontalBox, const int32 Score,
                                                     const FVector2D CharSize, const bool bWithSign)
{
	if (bWithSign)
	{
		if (Score >= 0)
		{
			AddSignTexture(ScoreHorizontalBox, true, CharSize);
		}
		else
		{
			AddSignTexture(ScoreHorizontalBox, false, CharSize);
		}
	}

	AddDigitTextures(ScoreHorizontalBox, Score, CharSize);
}

void UPXDigitTextureManager::AddSignTexture(UHorizontalBox* ScoreHorizontalBox, const bool bPositive,
                                            const FVector2D CharSize)
{
	if (!PXDigitTexturesDA)
	{
		UE_LOG(LogAssetData, Warning, TEXT("UPXDigitTextureManager::AddSignTexture|PXDigitTexturesDA is nullptr"))
		return;
	}

	UTexture2D* SignTexture = PXDigitTexturesDA->GetSignTexture(bPositive);
	AddToHorizontalBox(ScoreHorizontalBox, SignTexture, CharSize);
}

void UPXDigitTextureManager::AddDigitTextures(UHorizontalBox* ScoreHorizontalBox, const int32 Score,
                                              const FVector2D CharSize)
{
	if (!PXDigitTexturesDA)
	{
		UE_LOG(LogAssetData, Warning, TEXT("UPXDigitTextureManager::AddDigitTextures|PXDigitTexturesDA is nullptr"))
		return;
	}

	TArray<int32> DigitsArray = ConvertScoreIntoArray(Score);

	// Add all digits into horizontal box
	for (const int32 Digit : DigitsArray)
	{
		UTexture2D* DigitTexture = PXDigitTexturesDA->GetDigitTexture(Digit);

		AddToHorizontalBox(ScoreHorizontalBox, DigitTexture, CharSize);
	}
}

void UPXDigitTextureManager::AddToHorizontalBox(UHorizontalBox* ScoreHorizontalBox, UTexture2D* Texture,
                                                const FVector2D CharSize)
{
	if (!ScoreHorizontalBox)
	{
		UE_LOG(LogWidget, Warning, TEXT("UPXDigitTextureManager::AddToHorizontalBox|ScoreHorizontalBox is nullptr"))
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

TArray<int32> UPXDigitTextureManager::ConvertScoreIntoArray(const int32 Score) const
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
	// If the original number is 0, add a single 0 digit
	if (DigitArray.Num() == 0)
	{
		DigitArray.Add(0);
	}

	return DigitArray;
}
