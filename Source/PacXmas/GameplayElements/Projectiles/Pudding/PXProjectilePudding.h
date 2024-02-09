// Copyright (c) 2023 Smoking Carrots. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "PacXmas/GameplayElements/Projectiles/PXProjectile.h"
#include "PacXmas/Subsystems/ScoreSubsystem/PXScoreSubsystem.h"
#include "PXProjectilePudding.generated.h"

class UPXScoreSubsystem;
class APXSplashedPudding;

UCLASS()
class PACXMAS_API APXProjectilePudding : public APXProjectile
{
	GENERATED_BODY()

public:
	APXProjectilePudding();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                            UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep,
	                            const FHitResult& SweepResult);

private:
	void InitializeScoreSubsystem();

	void AddAndPopupScore(const EScoreTypes ScoreType) const;

	void SpawnPuddingOnMap() const;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<APXSplashedPudding> SplashedPuddingClass;

	UPROPERTY()
	UPXScoreSubsystem* PXScoreSubsystem{nullptr};
};
