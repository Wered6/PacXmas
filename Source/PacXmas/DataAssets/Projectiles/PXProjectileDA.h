// Copyright (c) 2023 Smoking Carrots. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PXProjectileDA.generated.h"

class UPaperSprite;

UCLASS()
class PACXMAS_API UPXProjectileDA : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	UPaperSprite* ProjectileSprite{nullptr};
};
