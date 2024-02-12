// Copyright (c) 2023 Smoking Carrots. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PXDigitTexturesDA.generated.h"

UCLASS()
class PACXMAS_API UPXDigitTexturesDA : public UDataAsset
{
	GENERATED_BODY()

public:
	UTexture2D* GetDigitTexture(const uint8_t Digit) const;
	UTexture2D* GetSignTexture(const bool bPositive) const;

private:
	UPROPERTY(EditDefaultsOnly)
	TArray<UTexture2D*> DigitTextures;
	UPROPERTY(EditDefaultsOnly)
	TArray<UTexture2D*> SignTextures;
};
