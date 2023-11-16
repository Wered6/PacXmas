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
	bool CanMoveInDirection(const FVector& Direction);

	FVector CurrentDirection{FVector::ZeroVector};

	UPROPERTY(EditAnywhere)
	float MoveCheckDistance{1.5f};
	UPROPERTY(EditAnywhere)
	float TurnProbability{0.8f};

	int32 DirectionChangeCooldown{0};
	const int32 MaxCooldown{35};
};
