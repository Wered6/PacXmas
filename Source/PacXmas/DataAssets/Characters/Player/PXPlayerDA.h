// Copyright (c) 2023 Smoking Carrots. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "PacXmas/DataAssets/Characters/PXCharacterDA.h"
#include "PXPlayerDA.generated.h"

UCLASS()
class PACXMAS_API UPXPlayerDA : public UPXCharacterDA
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category="Game Over")
	UPaperFlipbook* GameOverFB{nullptr};
};
