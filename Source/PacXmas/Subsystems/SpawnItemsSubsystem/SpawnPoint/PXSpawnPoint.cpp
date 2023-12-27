// Copyright (c) 2023 Santa Claus. All rights reserved.


#include "PXSpawnPoint.h"

APXSpawnPoint::APXSpawnPoint()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APXSpawnPoint::BeginPlay()
{
	Super::BeginPlay();
}

void APXSpawnPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
