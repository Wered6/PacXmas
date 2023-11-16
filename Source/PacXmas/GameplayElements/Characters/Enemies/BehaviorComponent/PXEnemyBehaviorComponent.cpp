// Copyright (c) 2023 Santa Claus. All rights reserved.

template <typename T>
void ShuffleArray(TArray<T>& Array)
{
	for (int32 Index = Array.Num() - 1; Index > 0; --Index)
	{
		int32 SwapIndex = FMath::RandRange(0, Index);
		Array.Swap(Index, SwapIndex);
	}
}

#include "PXEnemyBehaviorComponent.h"
#include "PacXmas/GameplayElements/Characters/Enemies/PXEnemy.h"

UPXEnemyBehaviorComponent::UPXEnemyBehaviorComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	CurrentDirection = FVector::UpVector;
}

void UPXEnemyBehaviorComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UPXEnemyBehaviorComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                              FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (DirectionChangeCooldown > 0)
	{
		DirectionChangeCooldown--;
		UE_LOG(LogTemp, Warning, TEXT("%d"), DirectionChangeCooldown);
	}
}

FVector UPXEnemyBehaviorComponent::DetermineNextDirection()
{
	const APXEnemy* PXEnemy = Cast<APXEnemy>(GetOwner());
	if (!PXEnemy)
	{
		return CurrentDirection;
	}

	TArray<FVector> PossibleDirections =
	{
		FVector::UpVector,
		FVector::ForwardVector,
		FVector::DownVector,
		FVector::BackwardVector
	};

	PossibleDirections.Remove(-CurrentDirection);
	ShuffleArray(PossibleDirections);

	bool bFoundDirection{false};
	FVector SelectedDirection{CurrentDirection};

	if (DirectionChangeCooldown <= 0)
	{
		for (const FVector& Dir : PossibleDirections)
		{
			if (CanMoveInDirection(Dir) && (Dir == CurrentDirection || FMath::RandRange(0.f, 1.f) < TurnProbability))
			{
				SelectedDirection = Dir;
				bFoundDirection = true;
				break;
			}
		}

		if (!bFoundDirection)
		{
			SelectedDirection = -CurrentDirection;
		}

		if (SelectedDirection != CurrentDirection)
		{
			DirectionChangeCooldown = MaxCooldown;
		}
	}

	CurrentDirection = SelectedDirection;
	return CurrentDirection;
}

bool UPXEnemyBehaviorComponent::CanMoveInDirection(const FVector& Direction)
{
	const APXEnemy* PXEnemy = Cast<APXEnemy>(GetOwner());
	if (PXEnemy)
	{
		return PXEnemy->CanMoveInDirection(Direction, MoveCheckDistance);
	}

	return false;
}
