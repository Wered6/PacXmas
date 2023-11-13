// Copyright (c) 2023 Santa Claus. All rights reserved.


#include "PXCharacter.h"

APXCharacter::APXCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APXCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void APXCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APXCharacter::MoveHorizontal(const float Value)
{
	AddMovementInput(FVector::ForwardVector, Value);
}

void APXCharacter::MoveVertical(const float Value)
{
	AddMovementInput(FVector::UpVector, Value);
}
