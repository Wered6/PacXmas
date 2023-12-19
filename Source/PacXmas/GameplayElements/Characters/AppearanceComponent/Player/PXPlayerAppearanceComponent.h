// Copyright (c) 2023 Santa Claus. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "PacXmas/GameplayElements/Characters/AppearanceComponent/PXAppearanceComponent.h"
#include "PXPlayerAppearanceComponent.generated.h"

UENUM()
enum class EPlayerLook : int
{
	Default,
	Pudding,
	MusicSheet,
	PuddingMusicSheet
};

UCLASS()
class PACXMAS_API UPXPlayerAppearanceComponent : public UPXAppearanceComponent
{
	GENERATED_BODY()

public:
	void SetDataAsset(const EPlayerLook PlayerLook);

private:
	UPROPERTY(EditDefaultsOnly, Category="DataAssets|PlayerPudding")
	UPXCharacterDA* PlayerPuddingDA{nullptr};
	UPROPERTY(EditDefaultsOnly, Category="DataAssets|PlayerMusicSheet")
	UPXCharacterDA* PlayerMusicSheetDA{nullptr};
	UPROPERTY(EditDefaultsOnly, Category="DataAssets|PlayerPuddingMusicSheet")
	UPXCharacterDA* PlayerPuddingMusicSheet{nullptr};
};
