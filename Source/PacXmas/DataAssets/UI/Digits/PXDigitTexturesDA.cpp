// Copyright (c) 2023 Smoking Carrots. All rights reserved.


#include "PXDigitTexturesDA.h"

UTexture2D* UPXDigitTexturesDA::GetDigitTexture(const uint8_t Digit) const
{
	if (!DigitTextures.IsValidIndex(Digit))
	{
		UE_LOG(LogAssetData, Warning,
		       TEXT("UPXDigitTexturesDA::GetDigitTexture|%d is out of DigitTextures array bounds"), Digit)
		return nullptr;
	}
	if (!DigitTextures[Digit])
	{
		UE_LOG(LogAssetData, Warning, TEXT("UPXDigitTexturesDA::GetDigitTexture|DigitTextures[Digit] is nullptr"))
		return nullptr;
	}

	return DigitTextures[Digit];
}

UTexture2D* UPXDigitTexturesDA::GetSignTexture(const bool bPositive) const
{
	if (!SignTextures[0])
	{
		UE_LOG(LogAssetData, Warning, TEXT("UPXDigitTexturesDA::GetSignTexture|SignTextures[0] is nullptr"))
		return nullptr;
	}
	if (!SignTextures[1])
	{
		UE_LOG(LogAssetData, Warning, TEXT("UPXDigitTexturesDA::GetSignTexture|SignTextures[1] is nullptr"))
		return nullptr;
	}

	if (!bPositive)
	{
		return SignTextures[0];
	}

	return SignTextures[1];
}
