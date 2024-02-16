// Copyright (c) 2023 Smoking Carrots. All rights reserved.

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
	virtual UPaperFlipbook* GetFlashedFB() override;

	virtual UPaperFlipbook* GetEatingPuddingFB() override;

	virtual UPaperFlipbook* GetHitPuddingUpFB() override;
	virtual UPaperFlipbook* GetHitPuddingDownFB() override;
	virtual UPaperFlipbook* GetHitPuddingLeftFB() override;
	virtual UPaperFlipbook* GetHitPuddingRightFB() override;

private:
	UPROPERTY(EditDefaultsOnly, Category="Stunned|Flashed")
	UPaperFlipbook* FlashedFB{nullptr};

	UPROPERTY(EditDefaultsOnly, Category="Stunned|Pudding Hit|Eating Pudding")
	UPaperFlipbook* EatingPuddingFB{nullptr};

	UPROPERTY(EditDefaultsOnly, Category="Stunned|Pudding Hit|Get Hit")
	UPaperFlipbook* HitPuddingUpFB{nullptr};
	UPROPERTY(EditDefaultsOnly, Category="Stunned|Pudding Hit|Get Hit")
	UPaperFlipbook* HitPuddingDownFB{nullptr};
	UPROPERTY(EditDefaultsOnly, Category="Stunned|Pudding Hit|Get Hit")
	UPaperFlipbook* HitPuddingLeftFB{nullptr};
	UPROPERTY(EditDefaultsOnly, Category="Stunned|Pudding Hit|Get Hit")
	UPaperFlipbook* HitPuddingRightFB{nullptr};
};
