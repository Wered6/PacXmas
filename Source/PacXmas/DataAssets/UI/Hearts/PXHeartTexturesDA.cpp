// Copyright (c) 2023 Smoking Carrots. All rights reserved.


#include "PXHeartTexturesDA.h"

UTexture2D* UPXHeartTexturesDA::GetHeartTextureGirl() const
{
	if (!HeartTextureGirl)
	{
		UE_LOG(LogAssetData, Warning, TEXT("UPXHeartTexturesDA::GetHeartTextureGirl|HeartTextureGirl is nullptr"))
		return nullptr;
	}

	return HeartTextureGirl;
}

UTexture2D* UPXHeartTexturesDA::GetHeartTextureBoy() const
{
	if (!HeartTextureBoy)
	{
		UE_LOG(LogAssetData, Warning, TEXT("UPXHeartTexturesDA::GetheartTextureBoy|HeartTextureBoy is nullptr"))
		return nullptr;
	}

	return HeartTextureBoy;
}
