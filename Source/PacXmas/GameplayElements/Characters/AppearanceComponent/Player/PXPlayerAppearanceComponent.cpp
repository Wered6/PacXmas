// Copyright (c) 2023 Santa Claus. All rights reserved.


#include "PXPlayerAppearanceComponent.h"

void UPXPlayerAppearanceComponent::SetDataAsset(const EPlayerLook PlayerLook)
{
	if (!ActiveDA)
	{
		UE_LOG(LogAssetData, Warning, TEXT("UPXPlayerAppearanceComponent::SetDataAsset|ActiveDA is nullptr"))
		return;
	}
	if (!CharacterDA)
	{
		UE_LOG(LogAssetData, Warning, TEXT("UPXPlayerAppearanceComponent::SetDataAsset|CharacterDA is nullptr"))
		return;
	}
	if (!PlayerPuddingDA)
	{
		UE_LOG(LogAssetData, Warning, TEXT("UPXPlayerAppearanceComponent::SetDataAsset|PlayerPuddingDA is nullptr"))
		return;
	}
	if (!PlayerMusicSheetDA)
	{
		UE_LOG(LogAssetData, Warning, TEXT("UPXPlayerAppearanceComponent::SetDataAsset|PlayerMusicSheetDA is nullptr"))
		return;
	}
	if (!PlayerPuddingMusicSheet)
	{
		UE_LOG(LogAssetData, Warning,
		       TEXT("UPXPlayerAppearanceComponent::SetDataAsset|PlayerPuddingMusichSheetDA is nullptr"))
		return;
	}

	switch (PlayerLook)
	{
	case EPlayerLook::Default:
		ActiveDA = CharacterDA;
		break;
	case EPlayerLook::Pudding:
		ActiveDA = PlayerPuddingDA;
		break;
	case EPlayerLook::MusicSheet:
		ActiveDA = PlayerMusicSheetDA;
		break;
	case EPlayerLook::PuddingMusicSheet:
		ActiveDA = PlayerPuddingMusicSheet;
		break;
	default:
		break;
	}
}
