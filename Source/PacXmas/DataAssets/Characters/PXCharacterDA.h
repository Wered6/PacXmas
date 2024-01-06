// Copyright (c) 2023 Smoking Carrots. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PXCharacterDA.generated.h"

class UPaperFlipbook;

UCLASS()
class PACXMAS_API UPXCharacterDA : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category="Movement")
	UPaperFlipbook* IdleFB{nullptr};
	UPROPERTY(EditDefaultsOnly, Category="Movement")
	UPaperFlipbook* MoveUpFB{nullptr};
	UPROPERTY(EditDefaultsOnly, Category="Movement")
	UPaperFlipbook* MoveDownFB{nullptr};
	UPROPERTY(EditDefaultsOnly, Category="Movement")
	UPaperFlipbook* MoveRightFB{nullptr};
	UPROPERTY(EditDefaultsOnly, Category="Movement")
	UPaperFlipbook* MoveLeftFB{nullptr};
};
