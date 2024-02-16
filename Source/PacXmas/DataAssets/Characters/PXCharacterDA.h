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
	UPaperFlipbook* GetIdleFB() const;
	UPaperFlipbook* GetMoveUpFB() const;
	UPaperFlipbook* GetMoveDownFB() const;
	UPaperFlipbook* GetMoveRightFB() const;
	UPaperFlipbook* GetMoveLeftFB() const;

private:
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

public:
	// virtual for PXEnemyDA
	virtual UPaperFlipbook* GetFlashedFB();
	virtual UPaperFlipbook* GetEatingPuddingFB();
	virtual UPaperFlipbook* GetHitPuddingUpFB();
	virtual UPaperFlipbook* GetHitPuddingDownFB();
	virtual UPaperFlipbook* GetHitPuddingLeftFB();
	virtual UPaperFlipbook* GetHitPuddingRightFB();

	// virtual for PXPlayerDA
	virtual UPaperFlipbook* GetGameOverFB();
};
