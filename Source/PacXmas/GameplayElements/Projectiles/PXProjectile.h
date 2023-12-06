// Copyright (c) 2023 Santa Claus. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PXProjectile.generated.h"

class UProjectileMovementComponent;
class UPXProjectileDA;
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

public:
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditDefaultsOnly)
	UProjectileMovementComponent* ProjectileMovementComponent{nullptr};
	
	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* CollisionComponent{nullptr};
	UPROPERTY(EditDefaultsOnly)
	UPaperSpriteComponent* PaperSpriteComponent{nullptr};

	UPROPERTY(EditDefaultsOnly, Category="DataAsset")
	UPXProjectileDA* ProjectileDA{nullptr};

	const float CollisionWidth{31.f};
	const float CollisionDepth{31.f};
	const float CollisionHeight{31.f};
};
