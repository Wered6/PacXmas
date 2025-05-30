// Copyright (c) 2023 Smoking Carrots. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PawnMovementComponent.h"
#include "PXCharacterMovementComponent.generated.h"

DECLARE_DYNAMIC_DELEGATE(FOnChangeDirectionDelegate);

DECLARE_DYNAMIC_DELEGATE(FOnStopMovingDelegate);

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
	FOnChangeDirectionDelegate OnChangeDirection;
	FOnStopMovingDelegate OnStopMoving;

	bool GetIsMoving() const;

	void SetCanMove(const bool bNewValue);
	bool GetCanMove() const;

protected:
	bool CanMoveInDirection(const FVector& Direction) const;

	virtual void HandleMovement(float DeltaTime);

	void UpdateRotation() const;
	void UpdateFlipbook() const;

	FVector CurrentDirection{FVector::ZeroVector};
	FVector TargetLocation{FVector::ZeroVector};
	bool bIsMoving{false};
	float TileSize{32.f};

	bool bFirstStop{true};

private:
	void MoveInDirection(const FVector& Direction, const float DeltaTime);
	bool HasReachedTargetLocation() const;
	void SetActorLocationToTargetLocation() const;
	ECollisionChannel GetCollisionChannelBasedOnOwnerClass() const;

	float MovementSpeed{200.f};
	bool bCanMove{true};

	float MoveCheckDistance{1.5f};
	float BorderProximityThreshold{1.f};
};
