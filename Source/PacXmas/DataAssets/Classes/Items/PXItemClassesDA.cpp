// Copyright (c) 2023 Smoking Carrots. All rights reserved.


#include "PXItemClassesDA.h"
#include "PacXmas/GameplayElements/Items/Fireworks/PXFireworks.h"
#include "PacXmas/GameplayElements/Items/MusicSheet/PXMusicSheet.h"
#include "PacXmas/GameplayElements/Items/Pudding/PXPudding.h"

TSubclassOf<APXPudding> UPXItemClassesDA::GetPuddingClass() const
{
	if (!PXPuddingClass)
	{
		UE_LOG(LogClass, Warning, TEXT("UPXItemsClassesDA::PXPuddingClass|PXPuddingClass is nullptr"))
		return nullptr;
	}

	return PXPuddingClass;
}

TSubclassOf<APXMusicSheet> UPXItemClassesDA::GetMusicSheetClass() const
{
	if (!PXMusicSheetClass)
	{
		UE_LOG(LogClass, Warning, TEXT("UPXItemsClassesDA::GetMusicSheetClass|PXMusicSheetClass is nullptr"))
		return nullptr;
	}

	return PXMusicSheetClass;
}

TSubclassOf<APXFireworks> UPXItemClassesDA::GetFireworksClass() const
{
	if (!PXFireworksClass)
	{
		UE_LOG(LogClass, Warning, TEXT("UPXItemsClassesDA::GetFireworksClass|PXFireworksClass is nullptr"))
		return nullptr;
	}

	return PXFireworksClass;
}
