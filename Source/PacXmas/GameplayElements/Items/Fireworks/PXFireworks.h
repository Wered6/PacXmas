// Copyright (c) 2023 Santa Claus. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "PacXmas/GameplayElements/Items/PXItem.h"
#include "PXFireworks.generated.h"

class UPXFlashSubsystem;

UCLASS()
class PACXMAS_API APXFireworks : public APXItem
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

protected:
	virtual void CollectItem(APXPlayer* PlayerCharacter) override;

private:
	UPROPERTY()
	UPXFlashSubsystem* FlashSubsystem{nullptr};
};
