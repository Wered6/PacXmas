// Copyright (c) 2023 Santa Claus. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PXItem.generated.h"

UCLASS()
class PACXMAS_API APXItem : public AActor
{
	GENERATED_BODY()

public:
	APXItem();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
};
