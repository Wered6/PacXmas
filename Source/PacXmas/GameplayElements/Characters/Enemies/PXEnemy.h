// Copyright (c) 2023 Smoking Carrots. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PacXmas/GameplayElements/Characters/PXCharacter.h"
#include "PXEnemy.generated.h"

class UPXEnemyMovementComponent;
class UPXEnemyAppearanceComponent;
class UPXEnemyBehaviorComponent;

UCLASS()
class PACXMAS_API APXEnemy : public APXCharacter
{
	GENERATED_BODY()

public:
	APXEnemy();

public:
	void EatPudding();
	void GetFlashed();

protected:
	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                            UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep,
	                            const FHitResult& SweepResult);

private:
	void StunYourself(const float Time);
	void ResumeMovement() const;

	FTimerHandle StunTimerHandle;

	float EatingPuddingTime{5.f};
	float FlashedTime{2.5f};

	UPROPERTY(EditDefaultsOnly)
	UPXEnemyAppearanceComponent* PXEnemyAppearanceComponent{nullptr};
	UPROPERTY()
	UPXEnemyMovementComponent* PXEnemyMovementComponent{nullptr};
};
