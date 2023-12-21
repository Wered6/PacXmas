// Copyright (c) 2023 Santa Claus. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "PacXmas/GameplayElements/Characters/AppearanceComponent/PXAppearanceComponent.h"
#include "PXPlayerAppearanceComponent.generated.h"

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
	UPROPERTY(EditDefaultsOnly, Category="Player Look|Pudding")
	UPXCharacterDA* PlayerPuddingDA{nullptr};
	UPROPERTY(EditDefaultsOnly, Category="Player Look|Music Sheet")
	UPXCharacterDA* PlayerMusicSheetDA{nullptr};
	UPROPERTY(EditDefaultsOnly, Category="Player Look|Pudding And Music Sheet")
	UPXCharacterDA* PlayerPuddingMusicSheet{nullptr};
};
