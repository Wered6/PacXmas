// Copyright (c) 2023 Santa Claus. All rights reserved.


#include "PacXmas/GameplayElements/Projectiles/MovementComponent/PXProjectileMovementComponent.h"

#include "PacXmas/GameplayElements/Projectiles/PXProjectile.h"
#include "PacXmas/Utilities/CustomLogs/PXCustomLogs.h"

UPXProjectileMovementComponent::UPXProjectileMovementComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UPXProjectileMovementComponent::BeginPlay()
{
	Super::BeginPlay();
}


void UPXProjectileMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                                   FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UPXProjectileMovementComponent::MoveInDirection(const float DeltaTime) const
{
	APXProjectile* PXProjectile = Cast<APXProjectile>(GetOwner());
	if (!PXProjectile)
	{
		UE_LOG(LogProjectile, Warning, TEXT("UPXProjectileMovementComponent::MoveInDirection|PXProjectile is nullptr"))
		return;
	}

	PXProjectile->AddActorLocalOffset(Direction * DeltaTime * Velocity);
}

void UPXProjectileMovementComponent::SetDirection(const FVector& NewDirection)
{
	Direction = NewDirection;
}
