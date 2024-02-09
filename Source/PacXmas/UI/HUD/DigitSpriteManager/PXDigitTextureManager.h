// Copyright (c) 2023 Smoking Carrots. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "PXDigitTextureManager.generated.h"

UCLASS(Blueprintable)
class PACXMAS_API UPXDigitTextureManager : public UObject
{
	GENERATED_BODY()

public:
	UTexture2D* GetDigitTexture(const uint8_t Digit);
	UTexture2D* GetSignTexture(const bool bPositive);

private:
	UPROPERTY(EditDefaultsOnly, Category="Digit Textures")
	TArray<UTexture2D*> DigitTextures;
	UPROPERTY(EditDefaultsOnly, Category="Sign Textures")
	TArray<UTexture2D*> SignTextures;
};
