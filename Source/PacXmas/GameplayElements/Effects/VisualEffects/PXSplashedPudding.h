// Copyright (c) 2023 Santa Claus. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PXSplashedPudding.generated.h"

class UPXSplashedPuddingDA;
class UPaperSpriteComponent;

UCLASS()
class PACXMAS_API APXSplashedPudding : public AActor
{
	GENERATED_BODY()

public:
	APXSplashedPudding();

	void SetRotationRelativeToProjectileDirection(const FVector& ProjectileForwardVector);
	void SetLocationRelativeToProjectile(const FVector& ProjectileForwardVector, const FVector& ProjectileLocation);
	
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	UPaperSpriteComponent* PaperSpriteComponent{nullptr};

	UPROPERTY(EditDefaultsOnly, Category="DataAsset")
	UPXSplashedPuddingDA* SplashedPuddingDA{nullptr};
};
