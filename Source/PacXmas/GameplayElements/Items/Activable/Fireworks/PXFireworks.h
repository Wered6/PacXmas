// Copyright (c) 2023 Santa Claus. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "PacXmas/GameplayElements/Items/Activable/PXItemActivable.h"
#include "PXFireworks.generated.h"

UCLASS()
class PACXMAS_API APXFireworks : public APXItemActivable
{
	GENERATED_BODY()

protected:
	virtual void CollectItem(APXPlayer* PlayerCharacter) override;
};
