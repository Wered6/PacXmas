// Copyright (c) 2023 Santa Claus. All rights reserved.


#include "PXInteractBoard.h"

APXInteractBoard::APXInteractBoard()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APXInteractBoard::BeginPlay()
{
	Super::BeginPlay();
}

void APXInteractBoard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
