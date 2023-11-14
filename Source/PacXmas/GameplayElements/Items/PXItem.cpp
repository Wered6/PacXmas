// Copyright (c) 2023 Santa Claus. All rights reserved.


#include "PXItem.h"

APXItem::APXItem()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APXItem::BeginPlay()
{
	Super::BeginPlay();
}

void APXItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
