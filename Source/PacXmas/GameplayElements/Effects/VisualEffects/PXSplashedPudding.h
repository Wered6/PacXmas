// Copyright (c) 2023 Santa Claus. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PXSplashedPudding.generated.h"

UCLASS()
class PACXMAS_API APXSplashedPudding : public AActor
{
	GENERATED_BODY()

public:
	APXSplashedPudding();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
};
