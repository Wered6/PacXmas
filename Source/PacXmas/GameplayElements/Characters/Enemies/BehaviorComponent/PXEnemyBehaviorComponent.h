// Copyright (c) 2023 Santa Claus. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PXEnemyBehaviorComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PACXMAS_API UPXEnemyBehaviorComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPXEnemyBehaviorComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

public:
	FVector DetermineNextDirection();

private:
	bool CanMoveInDirection(const FVector& Direction) const;
	bool CanMoveInAxis(const FVector& Axis) const;
	TArray<FVector> FilterPossibleDirections() const;
	FVector SelectDirectionFromPossibilities(const TArray<FVector>& Directions) const;

	FVector CurrentDirection{FVector::ZeroVector};

	float MoveCheckDistance{1.5f};
	float TurnProbability{0.8f};

	FVector BaseLocation{FVector::ZeroVector};
	float LocationOffset{32.f};

	int32 DirectionChangeCooldown{0};
	const int32 MaxCooldown{20};
};
