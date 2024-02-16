// Copyright (c) 2023 Smoking Carrots. All rights reserved.


#include "PXEnemyDA.h"

UPaperFlipbook* UPXEnemyDA::GetFlashedFB()
{
	if (!FlashedFB)
	{
		UE_LOG(LogAssetData, Warning, TEXT("UPXEnemyDA::GetFlashedFB|FlashedFB is nullptr"))
		return nullptr;
	}

	return FlashedFB;
}

UPaperFlipbook* UPXEnemyDA::GetEatingPuddingFB()
{
	if (!EatingPuddingFB)
	{
		UE_LOG(LogAssetData, Warning, TEXT("UPXEnemyDA::GetEatingPuddingFB|EatingPuddingFB is nullptr"))
		return nullptr;
	}

	return EatingPuddingFB;
}

UPaperFlipbook* UPXEnemyDA::GetHitPuddingUpFB()
{
	if (!HitPuddingUpFB)
	{
		UE_LOG(LogAssetData, Warning, TEXT("UPXEnemyDA::GetHitPuddingUpFB|HitPuddingUpFB is nullptr"))
		return nullptr;
	}

	return HitPuddingUpFB;
}

UPaperFlipbook* UPXEnemyDA::GetHitPuddingDownFB()
{
	if (!HitPuddingDownFB)
	{
		UE_LOG(LogAssetData, Warning, TEXT("UPXEnemyDA::GetHitPuddingDownFB|HitPuddingDownFB is nullptr"))
		return nullptr;
	}

	return HitPuddingDownFB;
}

UPaperFlipbook* UPXEnemyDA::GetHitPuddingLeftFB()
{
	if (!HitPuddingLeftFB)
	{
		UE_LOG(LogAssetData, Warning, TEXT("UPXEnemyDA::GetHitPuddingLeftFB|HitPuddingLeftFB is nullptr"))
		return nullptr;
	}

	return HitPuddingLeftFB;
}

UPaperFlipbook* UPXEnemyDA::GetHitPuddingRightFB()
{
	if (!HitPuddingRightFB)
	{
		UE_LOG(LogAssetData, Warning, TEXT("UPXEnemyDA::GetHitPuddingRightFB|HitPuddingRightFB is nullptr"))
		return nullptr;
	}

	return HitPuddingRightFB;
}
