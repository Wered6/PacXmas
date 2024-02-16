// Copyright (c) 2023 Smoking Carrots. All rights reserved.


#include "PXPlayerDA.h"

UPaperFlipbook* UPXPlayerDA::GetGameOverFB()
{
	if (!GameOverFB)
	{
		UE_LOG(LogAssetData, Warning, TEXT("UPXPlayerDA::GetGameOverFB|GameOverFB is nullptr"))
		return nullptr;
	}

	return GameOverFB;
}
