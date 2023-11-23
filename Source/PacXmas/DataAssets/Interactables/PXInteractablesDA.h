// Copyright (c) 2023 Santa Claus. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PXInteractablesDA.generated.h"

class UPaperSprite;

UCLASS()
class PACXMAS_API UPXInteractablesDA : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	UPaperSprite* SpriteComponent{nullptr};
};
