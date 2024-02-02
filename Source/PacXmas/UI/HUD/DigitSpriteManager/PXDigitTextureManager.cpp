// Copyright (c) 2023 Smoking Carrots. All rights reserved.


#include "PXDigitTextureManager.h"
#include "PacXmas/Utilities/CustomLogs/PXCustomLogs.h"

UTexture2D* UPXDigitTextureManager::GetDigitTexture(const uint8_t Digit)
{
	if (!DigitTextures.IsValidIndex(Digit))
	{
		UE_LOG(LogDigitTextureManager, Warning,
		       TEXT("UPXDigitTextureManager::GetDigitTexture|%d is out of DigitTextures array bounds"), Digit)
		return nullptr;
	}

	return DigitTextures[Digit];
}
