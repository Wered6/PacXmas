// Copyright (c) 2023 Santa Claus. All rights reserved.


#include "PacXmas/GameplayElements/Interactables/Board/PXBoard.h"

APXBoard::APXBoard()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APXBoard::BeginPlay()
{
	Super::BeginPlay();
}

void APXBoard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
