// Copyright (c) 2023 Smoking Carrots. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "PacXmas/GameplayElements/Items/PXItem.h"
#include "PXPudding.generated.h"

UCLASS()
class PACXMAS_API APXPudding : public APXItem
{
	GENERATED_BODY()

protected:
	virtual void CollectItem(APXPlayer* PXPlayer) override;
};
