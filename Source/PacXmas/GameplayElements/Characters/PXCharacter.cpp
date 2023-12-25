// Copyright (c) 2023 Santa Claus. All rights reserved.


#include "PXCharacter.h"
#include "Components/BoxComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "PacXmas/Utilities/CustomLogs/PXCustomLogs.h"

APXCharacter::APXCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collider"));
	RootComponent = CollisionComponent;
	CollisionComponent->SetCollisionProfileName(TEXT("BlockAllDynamic"));

	FloatingPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingPawnMovement"));

	if (!CollisionComponent)
	{
		UE_LOG(LogComponent, Warning, TEXT("APXCharacter::APXCharacter|CollisionComponent is nullptr"))
		return;
	}

	const FVector BoxExtent = FVector(CollisionSize / 2);
	CollisionComponent->SetBoxExtent(BoxExtent);
}

void APXCharacter::MoveHorizontal(const float Value)
{
	SetActorRotation(Value > 0 ? FRotator(0, 0, 0) : FRotator(180, 0, 0));
	AddMovementInput(FVector::ForwardVector, Value);
}

void APXCharacter::MoveVertical(const float Value)
{
	SetActorRotation(Value > 0 ? FRotator(90, 0, 0) : FRotator(-90, 0, 0));
	AddMovementInput(FVector::UpVector, Value);
}
