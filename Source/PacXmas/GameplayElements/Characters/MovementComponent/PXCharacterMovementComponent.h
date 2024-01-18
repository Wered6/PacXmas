// Copyright (c) 2023 Smoking Carrots. All rights reserved.

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

	void SetCanPlayerMove(const bool bNewValue);
	bool GetCanPlayerMove() const;

	// AI
	void SetIsAIControlled(const bool bNewValue);

	void SetCanAIMove(const bool bNewValue);
	bool GetCanAIMove() const;

private:
	bool CanMoveInDirection(const FVector& Direction) const;
	bool HasReachedTileBorder() const;
	void MoveInDirection(const FVector& Direction, const float DeltaTime);
	ECollisionChannel GetCollisionChannelBasedOnOwnerClass() const;

	void ResetTargetLocationIfTooFar();

	void HandlePlayerMovement(float DeltaTime);

	FVector DesiredDirection{FVector::ZeroVector};
	FVector CurrentDirection{FVector::ZeroVector};
	FVector NextDesiredDirection{FVector::ZeroVector};
	FVector TargetLocation;

	float TileSize{32.f};
	bool bIsMoving{false};
	float MovementSpeed{200.f};
	bool bCanPlayerMove{true};

	float MoveCheckDistance{1.5f};
	float BorderProximityThreshold{1.f};

	// AI
	void HandleAIMovement(float DeltaTime);
	FVector ChooseNewAIDirection() const;

	bool bIsAIControlled{false};
	float AccumulatedTime{0.f};
	float DecisionInterval{0.f};
	bool bCanAIMove{false};
};
