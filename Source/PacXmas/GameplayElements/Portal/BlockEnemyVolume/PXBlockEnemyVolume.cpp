// Copyright (c) 2023 Santa Claus. All rights reserved.


#include "PXBlockEnemyVolume.h"
#include "Components/BoxComponent.h"
#include "PacXmas/Utilities/CustomLogs/PXCustomLogs.h"

APXBlockEnemyVolume::APXBlockEnemyVolume()
{
	CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Component"));

	if (!CollisionComponent)
	{
		UE_LOG(LogComponent, Warning, TEXT("APXBlockEnemyVolume::APXBlockEnemyVolume|CollisionComponent is nullptr"))
		return;
	}

	RootComponent = CollisionComponent;
	
	const FVector BoxExtent = FVector(CollisionSize / 2);
	CollisionComponent->SetBoxExtent(BoxExtent);

	CollisionComponent->SetCollisionProfileName(TEXT("BlockEnemyVolume"));
}
