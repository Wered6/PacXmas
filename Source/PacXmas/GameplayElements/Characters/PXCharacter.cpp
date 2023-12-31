// Copyright (c) 2023 Smoking Carrots. All rights reserved.


#include "PXCharacter.h"
#include "Components/BoxComponent.h"
#include "MovementComponent/PXCharacterMovementComponent.h"
#include "PacXmas/Utilities/CustomLogs/PXCustomLogs.h"

APXCharacter::APXCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collider"));

	if (!CollisionComponent)
	{
		UE_LOG(LogComponent, Warning, TEXT("APXCharacter::APXCharacter|CollisionComponent is nullptr"))
		return;
	}

	RootComponent = CollisionComponent;

	const FVector BoxExtent = FVector(CollisionSize / 2);
	CollisionComponent->SetBoxExtent(BoxExtent);

	PXCharacterMovementComponent = CreateDefaultSubobject<UPXCharacterMovementComponent>(TEXT("Movement Component"));
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
