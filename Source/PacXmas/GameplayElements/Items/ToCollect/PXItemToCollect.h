// Copyright (c) 2023 Santa Claus. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "PacXmas/GameplayElements/Items/PXItem.h"
#include "PXItemToCollect.generated.h"

class APXPlayer;

UCLASS()
class PACXMAS_API APXItemToCollect : public APXItem
{
	GENERATED_BODY()

public:
	APXItemToCollect();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaSeconds) override;
};
