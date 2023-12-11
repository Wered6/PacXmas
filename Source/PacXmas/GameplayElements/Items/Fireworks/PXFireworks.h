// Copyright (c) 2023 Santa Claus. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "PacXmas/GameplayElements/Items/PXItem.h"
#include "PXFireworks.generated.h"

UCLASS()
class PACXMAS_API APXFireworks : public APXItem
{
	GENERATED_BODY()

protected:
	virtual void CollectItem(APXPlayer* PlayerCharacter) override;
};
