// Copyright (c) 2023 Santa Claus. All rights reserved.


#include "PXCharacter.h"
#include "Components/BoxComponent.h"
#include "PacXmas/Utilities/CustomLogs/PXCustomLogs.h"

APXCharacter::APXCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collider"));
	RootComponent = CollisionComponent;
	CollisionComponent->SetCollisionProfileName(TEXT("BlockAllDynamic"));


	if (!CollisionComponent)
	{
		UE_LOG(LogComponent, Warning, TEXT("APXCharacter::APXCharacter|CollisionComponent is nullptr"))
		return;
	}

	const FVector BoxExtent = FVector(CollisionSize / 2);
	CollisionComponent->SetBoxExtent(BoxExtent);
}

FVector APXCharacter::GetScaledBoxExtent() const
{
	if (!CollisionComponent)
	{
		UE_LOG(LogComponent, Warning, TEXT("APXCharacter::GetScaledBoxExtent|CollisionComponent is nullptr"))
		return FVector::ZeroVector;
	}

	return CollisionComponent->GetScaledBoxExtent();
}
