// Copyright (c) 2023 Smoking Carrots. All rights reserved.


#include "PXCharacterDA.h"

UPaperFlipbook* UPXCharacterDA::GetIdleFB() const
{
	if (!IdleFB)
	{
		UE_LOG(LogAssetData, Warning, TEXT("UPXCharacterDA::GetIdleFB|IdleFB is nullptr"))
		return nullptr;
	}

	return IdleFB;
}

UPaperFlipbook* UPXCharacterDA::GetMoveUpFB() const
{
	if (!MoveUpFB)
	{
		UE_LOG(LogAssetData, Warning, TEXT("UPXCharacterDA::GetMoveUpFB|MoveUpFB is nullptr"))
		return nullptr;
	}

	return MoveUpFB;
}

UPaperFlipbook* UPXCharacterDA::GetMoveDownFB() const
{
	if (!MoveDownFB)
	{
		UE_LOG(LogAssetData, Warning, TEXT("UPXCharacterDA::GetMoveDownFB|MoveDownFB is nullptr"))
		return nullptr;
	}

	return MoveDownFB;
}

UPaperFlipbook* UPXCharacterDA::GetMoveRightFB() const
{
	if (!MoveRightFB)
	{
		UE_LOG(LogAssetData, Warning, TEXT("UPXCharacterDA::GetMoveRightFB|MoveRightFB is nullptr"))
		return nullptr;
	}

	return MoveRightFB;
}

UPaperFlipbook* UPXCharacterDA::GetMoveLeftFB() const
{
	if (!MoveLeftFB)
	{
		UE_LOG(LogAssetData, Warning, TEXT("UPXCharacterDA::GetMoveLeftFB|MoveLeftFB is nullptr"))
		return nullptr;
	}

	return MoveLeftFB;
}

UPaperFlipbook* UPXCharacterDA::GetFlashedFB()
{
	UE_LOG(LogVirtualization, Warning, TEXT("UPXCharacterDA::GetFlashedFB|This is virtual function."))
	return nullptr;
}

UPaperFlipbook* UPXCharacterDA::GetEatingPuddingFB()
{
	UE_LOG(LogVirtualization, Warning, TEXT("UPXCharacterDA::GetEatingPuddingFB|This is virtual function."))
	return nullptr;
}

UPaperFlipbook* UPXCharacterDA::GetHitPuddingUpFB()
{
	UE_LOG(LogVirtualization, Warning, TEXT("UPXCharacterDA::GetHitPuddingUpFB|This is virtual function."))
	return nullptr;
}

UPaperFlipbook* UPXCharacterDA::GetHitPuddingDownFB()
{
	UE_LOG(LogVirtualization, Warning, TEXT("UPXCharacterDA::GetHitPuddingDownFB|This is virtual function."))
	return nullptr;
}

UPaperFlipbook* UPXCharacterDA::GetHitPuddingLeftFB()
{
	UE_LOG(LogVirtualization, Warning, TEXT("UPXCharacterDA::GetHitPuddingLeftFB|This is virtual function."))
	return nullptr;
}

UPaperFlipbook* UPXCharacterDA::GetHitPuddingRightFB()
{
	UE_LOG(LogVirtualization, Warning, TEXT("UPXCharacterDA::GetHitPuddingRightFB|This is virtual function."))
	return nullptr;
}

UPaperFlipbook* UPXCharacterDA::GetGameOverFB()
{
	UE_LOG(LogVirtualization, Warning, TEXT("UPXCharacterDA::GetGameOverFB|This is virtual function."))
	return nullptr;
}
