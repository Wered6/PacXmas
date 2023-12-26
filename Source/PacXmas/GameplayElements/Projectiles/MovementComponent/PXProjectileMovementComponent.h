// Copyright (c) 2023 Santa Claus. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PXProjectileMovementComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PACXMAS_API UPXProjectileMovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPXProjectileMovementComponent();

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

private:
	void MoveInDirection(const float DeltaTime) const;

	float Velocity{300.f};
};
