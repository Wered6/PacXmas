// Copyright (c) 2023 Santa Claus. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PXPortal.generated.h"

UCLASS()
class PACXMAS_API APXPortal : public AActor
{
	GENERATED_BODY()

public:
	APXPortal();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
};
