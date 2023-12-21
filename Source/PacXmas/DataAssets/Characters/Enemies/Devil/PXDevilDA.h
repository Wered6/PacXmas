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
	UPaperFlipbook* GetHitPuddingUpFB{nullptr};
	UPROPERTY(EditDefaultsOnly, Category="Getting Hit")
	UPaperFlipbook* GetHitPuddingDownFB{nullptr};
	UPROPERTY(EditDefaultsOnly, Category="Getting Hit")
	UPaperFlipbook* GetHitPuddingRightFB{nullptr};
	UPROPERTY(EditDefaultsOnly, Category="Getting Hit")
	UPaperFlipbook* GetHitPuddingLeftFB{nullptr};
};
