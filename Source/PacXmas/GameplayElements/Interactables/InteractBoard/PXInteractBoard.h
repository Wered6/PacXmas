// Copyright (c) 2023 Santa Claus. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PXInteractBoard.generated.h"

UCLASS()
class PACXMAS_API APXInteractBoard : public AActor
{
	GENERATED_BODY()

public:
	APXInteractBoard();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
};
