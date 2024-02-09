// Copyright (c) 2023 Smoking Carrots. All rights reserved.


#include "PXDigitTextureManager.h"
#include "PacXmas/Utilities/CustomLogs/PXCustomLogs.h"

UTexture2D* UPXDigitTextureManager::GetDigitTexture(const uint8_t Digit)
{
	if (!DigitTextures.IsValidIndex(Digit))
	{
		UE_LOG(LogManager, Warning,
		       TEXT("UPXDigitTextureManager::GetDigitTexture|%d is out of DigitTextures array bounds"), Digit)
		return nullptr;
	}

	return DigitTextures[Digit];
}

UTexture2D* UPXDigitTextureManager::GetSignTexture(const bool bPositive)
{
	if (!SignTextures.IsValidIndex(0))
	{
		UE_LOG(LogManager, Warning,
		       TEXT("UPXDigitTextureManager::GetSignTexture|Index 0 is out of SignTextures array bounds"))
		return nullptr;
	}
	if (!SignTextures.IsValidIndex(1))
	{
		UE_LOG(LogManager, Warning,
		       TEXT("UPXDigitTextureManager::GetSignTexture|Index 1 is out of SignTextures array bounds"))
		return nullptr;
	}

	if (!bPositive)
	{
		return SignTextures[0];
	}

	return SignTextures[1];
}
