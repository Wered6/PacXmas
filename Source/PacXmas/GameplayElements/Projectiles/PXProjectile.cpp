// Copyright (c) 2023 Santa Claus. All rights reserved.


#include "PXProjectile.h"

APXProjectile::APXProjectile()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APXProjectile::BeginPlay()
{
	Super::BeginPlay();
}

void APXProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
