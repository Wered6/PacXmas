// Copyright (c) 2023 Smoking Carrots. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PXItemClassesDA.generated.h"

class APXFireworks;
class APXMusicSheet;
class APXPudding;

UCLASS()
class PACXMAS_API UPXItemClassesDA : public UDataAsset
{
	GENERATED_BODY()

public:
	TSubclassOf<APXPudding> GetPuddingClass() const;
	TSubclassOf<APXMusicSheet> GetMusicSheetClass() const;
	TSubclassOf<APXFireworks> GetFireworksClass() const;

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<APXPudding> PXPuddingClass;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<APXMusicSheet> PXMusicSheetClass;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<APXFireworks> PXFireworksClass;
};
