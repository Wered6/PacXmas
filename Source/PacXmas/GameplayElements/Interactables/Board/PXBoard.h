// Copyright (c) 2023 Santa Claus. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PXBoard.generated.h"

UCLASS()
class PACXMAS_API APXBoard : public AActor
{
	GENERATED_BODY()

public:
	APXBoard();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
};
