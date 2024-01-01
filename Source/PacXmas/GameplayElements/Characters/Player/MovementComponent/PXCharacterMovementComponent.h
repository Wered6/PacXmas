// Copyright (c) 2023 Santa Claus. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PawnMovementComponent.h"
#include "PXCharacterMovementComponent.generated.h"

UCLASS()
class PACXMAS_API UPXCharacterMovementComponent : public UPawnMovementComponent
{
	GENERATED_BODY()

public:
	UPXCharacterMovementComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

public:
	void SetDesiredDirection(const FVector& NewDirection);
	bool GetIsMoving() const;

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

	inline static FVector DefaultDesiredDirection{FVector::ZeroVector};
	inline static FVector DefaultCurrentDirection{FVector::ZeroVector};

	static constexpr float DefaultTileSize{32.f};
	static constexpr bool bDefaultIsMoving{false};
	static constexpr float DefaultMovementSpeed{200.f};
	
	static constexpr float MoveCheckDistance{1.5f};
	static constexpr float BorderProximityThreshold{1.f};
};
