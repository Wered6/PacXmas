// Copyright (c) 2023 Smoking Carrots. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "PacXmas/GameplayElements/Items/PXItem.h"
#include "PXFireworks.generated.h"

class UPXScoreSubsystem;
class UPXFlashSubsystem;

UCLASS()
class PACXMAS_API APXFireworks : public APXItem
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

protected:
	virtual void CollectItem(APXPlayer* PXPlayer) override;

private:
	void InitializeFlashSubsystem();
	void InitializeScoreSubsystem();

	void FlashAllEnemies() const;

	void RespawnFireworks() const;

	void AddAndPopupScore(const APXPlayer* PXPlayer) const;

	UPROPERTY()
	UPXFlashSubsystem* PXFlashSubsystem{nullptr};

	UPROPERTY()
	UPXScoreSubsystem* PXScoreSubsystem{nullptr};
};
