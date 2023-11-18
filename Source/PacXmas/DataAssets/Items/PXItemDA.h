// Copyright (c) 2023 Santa Claus. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PXItemDA.generated.h"

class UPaperSprite;

UCLASS()
class PACXMAS_API UPXItemDA : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Sprites")
	UPaperSprite* SpriteComp{nullptr};
};
