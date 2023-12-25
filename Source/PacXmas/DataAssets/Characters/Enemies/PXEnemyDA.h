// Copyright (c) 2023 Santa Claus. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "PacXmas/DataAssets/Characters/PXCharacterDA.h"
#include "PXEnemyDA.generated.h"

class UPaperFlipbook;

UCLASS()
class PACXMAS_API UPXEnemyDA : public UPXCharacterDA
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category="Stunned|Flashed")
	UPaperFlipbook* FlashedFB{nullptr};
	
	UPROPERTY(EditDefaultsOnly, Category="Stunned|Pudding Hit|Eating Pudding")
	UPaperFlipbook* EatingPuddingFB{nullptr};
	
	UPROPERTY(EditDefaultsOnly, Category="Stunned|Pudding Hit|Get Hit")
	UPaperFlipbook* GetHitPuddingUp{nullptr};
	UPROPERTY(EditDefaultsOnly, Category="Stunned|Pudding Hit|Get Hit")
	UPaperFlipbook* GetHitPuddingDown{nullptr};
	UPROPERTY(EditDefaultsOnly, Category="Stunned|Pudding Hit|Get Hit")
	UPaperFlipbook* GetHitPuddingLeft{nullptr};
	UPROPERTY(EditDefaultsOnly, Category="Stunned|Pudding Hit|Get Hit")
	UPaperFlipbook* GetHitPuddingRight{nullptr};
};
