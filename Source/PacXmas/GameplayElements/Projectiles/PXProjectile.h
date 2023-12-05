// Copyright (c) 2023 Santa Claus. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PXProjectile.generated.h"

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
	UBoxComponent* CollisionComponent{nullptr};
	UPROPERTY(EditDefaultsOnly)
	UPaperSpriteComponent* PaperSpriteComponent{nullptr};

	UPROPERTY(EditDefaultsOnly, Category="DataAsset")
	UPXProjectileDA* ProjectileDA{nullptr};
};
