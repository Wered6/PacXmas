// Copyright (c) 2023 Smoking Carrots. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/HorizontalBox.h"
#include "PXDigitTextureManager.generated.h"

class UHorizontalBox;
class UPXDigitTexturesDA;

UCLASS(Blueprintable)
class PACXMAS_API UPXDigitTextureManager : public UObject
{
	GENERATED_BODY()

public:
	void SetScoreInHorizontalBox(UHorizontalBox* ScoreHorizontalBox, const int32 Score, const FVector2D CharSize,
	                             const bool bWithSign = false);

private:
	void AddSignTexture(UHorizontalBox* ScoreHorizontalBox, const bool bPositive, const FVector2D CharSize);
	void AddDigitTextures(UHorizontalBox* ScoreHorizontalBox, const int32 Score, const FVector2D CharSize);

	void AddToHorizontalBox(UHorizontalBox* ScoreHorizontalBox, UTexture2D* Texture, const FVector2D CharSize);
	TArray<int32> ConvertScoreIntoArray(const int32 Score) const;

	UPROPERTY(EditDefaultsOnly, Category="Data Assets|Textures|Digits")
	UPXDigitTexturesDA* PXDigitTexturesDA{nullptr};
};
