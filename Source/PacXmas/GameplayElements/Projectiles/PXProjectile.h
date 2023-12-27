// Copyright (c) 2023 Santa Claus. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PXProjectile.generated.h"

class UPXProjectileDA;
class UPXProjectileMovementComponent;
class UPaperSpriteComponent;
class UBoxComponent;

UCLASS()
class PACXMAS_API APXProjectile : public AActor
{
	GENERATED_BODY()

public:
	APXProjectile();

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY()
	UBoxComponent* CollisionComponent{nullptr};

private:
	UPROPERTY()
	UPaperSpriteComponent* PaperSpriteComponent{nullptr};
	UPROPERTY()
	UPXProjectileMovementComponent* ProjectileMovementComponent{nullptr};

	UPROPERTY(EditDefaultsOnly, Category="DataAsset")
	UPXProjectileDA* ProjectileDA{nullptr};

	const float CollisionSize{29.f};
};
