// Copyright (c) 2023 Santa Claus. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "PacXmas/DataAssets/Characters/PXCharacterDA.h"
#include "PXDevilDA.generated.h"

UCLASS()
class PACXMAS_API UPXDevilDA : public UPXCharacterDA
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category="Eating Pudding")
	UPaperFlipbook* EatingPuddingFB{nullptr};
	UPROPERTY(EditDefaultsOnly, Category="Getting Hit")
	UPaperFlipbook* GettingHitUpFB{nullptr};
	UPROPERTY(EditDefaultsOnly, Category="Getting Hit")
	UPaperFlipbook* GettingHitDownFB{nullptr};
	UPROPERTY(EditDefaultsOnly, Category="Getting Hit")
	UPaperFlipbook* GettingHitRightFB{nullptr};
	UPROPERTY(EditDefaultsOnly, Category="Getting Hit")
	UPaperFlipbook* GettingHitLeftFB{nullptr};
};
