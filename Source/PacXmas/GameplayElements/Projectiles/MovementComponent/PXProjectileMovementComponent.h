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

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

public:
	void SetDirection(const FVector& Direction);

private:
	void MoveInDirection(const float DeltaTime) const;

	FVector Direction{FVector::ZeroVector};
	float Velocity{500.f};
};
