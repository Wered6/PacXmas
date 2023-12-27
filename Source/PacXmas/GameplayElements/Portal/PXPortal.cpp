// Copyright (c) 2023 Santa Claus. All rights reserved.


#include "PXPortal.h"

APXPortal::APXPortal()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APXPortal::BeginPlay()
{
	Super::BeginPlay();
}

void APXPortal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
