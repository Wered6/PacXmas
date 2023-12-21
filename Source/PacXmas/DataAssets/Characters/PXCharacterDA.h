// Copyright (c) 2023 Santa Claus. All rights reserved.

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
	UPROPERTY(EditDefaultsOnly, Category="Walking")
	UPaperFlipbook* IdleFB{nullptr};
	UPROPERTY(EditDefaultsOnly, Category="Walking")
	UPaperFlipbook* WalkUpFB{nullptr};
	UPROPERTY(EditDefaultsOnly, Category="Walking")
	UPaperFlipbook* WalkDownFB{nullptr};
	UPROPERTY(EditDefaultsOnly, Category="Walking")
	UPaperFlipbook* WalkRightFB{nullptr};
	UPROPERTY(EditDefaultsOnly, Category="Walking")
	UPaperFlipbook* WalkLeftFB{nullptr};
};
