// Copyright (c) 2023 Santa Claus. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PXProjectile.generated.h"

class APXSplashedPudding;
class UPXProjectileDA;
class UPaperSpriteComponent;
class UBoxComponent;
class UPXProjectileMovementComponent;

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

public:
	void SetActorRotationBasedOnLastMoveDirection(const FVector& LastMoveDirection);

	void SetIsSpawned(const bool bSpawned);
	
protected:
	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                            UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep,
	                            const FHitResult& SweepResult);

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<APXSplashedPudding> SplashedPuddingClass{nullptr};

	UPROPERTY()
	UPXProjectileMovementComponent* ProjectileMovementComponent{nullptr};

	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* CollisionComponent{nullptr};
	UPROPERTY(EditDefaultsOnly)
	UPaperSpriteComponent* PaperSpriteComponent{nullptr};

	UPROPERTY(EditDefaultsOnly, Category="DataAsset")
	UPXProjectileDA* ProjectileDA{nullptr};

	const float CollisionSize{30.f};

	bool bIsSpawned{false};
};
