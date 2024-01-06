// Copyright (c) 2023 Smoking Carrots. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PXSplashedPuddingDA.generated.h"

class UPaperSprite;

UCLASS()
class PACXMAS_API UPXSplashedPuddingDA : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	UPaperSprite* SplashedPuddingSprite{nullptr};
};
