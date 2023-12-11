// Copyright (c) 2023 Santa Claus. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "PacXmas/GameplayElements/Items/PXItem.h"
#include "PXPudding.generated.h"

UCLASS()
class PACXMAS_API APXPudding : public APXItem
{
	GENERATED_BODY()

	virtual void CollectItem(APXPlayer* PlayerCharacter) override;
};
