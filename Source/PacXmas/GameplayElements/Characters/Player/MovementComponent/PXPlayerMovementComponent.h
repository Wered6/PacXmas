// Copyright (c) 2023 Santa Claus. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PawnMovementComponent.h"
#include "PXPlayerMovementComponent.generated.h"

UCLASS()
class PACXMAS_API UPXPlayerMovementComponent : public UPawnMovementComponent
{
	GENERATED_BODY()

public:
	UPXPlayerMovementComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

public:
	void SetDesiredDirection(const FVector& NewDirection);

private:
	bool HasReachedDecisionPoint() const;
	bool CanMoveInDirection(const FVector& Direction) const;
	bool HasReachedTileBorder() const;
	void MoveInDirection(const FVector& Direction, const float DeltaTime);

	FVector DesiredDirection;
	FVector CurrentDirection;
	FVector NextDesiredDirection;
	
	FVector TargetLocation;
	float TileSize;
	bool bIsMoving;
	float MovementSpeed;

	static constexpr float DefaultTileSize{32.f};
	static constexpr float DefaultMovementSpeed{300.f};
	static constexpr float MoveCheckDistance{1.5f};
	static constexpr float BorderProximityThreshold{1.f};
};
