// Copyright (c) 2023 Santa Claus. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PXSpawnPoint.generated.h"

UCLASS()
class PACXMAS_API APXSpawnPoint : public AActor
{
	GENERATED_BODY()

public:
	APXSpawnPoint();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
};
