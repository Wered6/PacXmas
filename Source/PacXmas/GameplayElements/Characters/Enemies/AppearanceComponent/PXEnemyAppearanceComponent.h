// Copyright (c) 2023 Smoking Carrots. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "PXEnemyAppearanceComponent.generated.h"

class UPaperFlipbookComponent;
class UPXEnemyDA;

enum class EEnemyGetHitPudding : uint8
{
	Up,
	Down,
	Left,
	Right
};

UCLASS()
class PACXMAS_API UPXEnemyAppearanceComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPXEnemyAppearanceComponent();

protected:
	virtual void BeginPlay() override;

	virtual void OnRegister() override;

public:
	void SetFlipbookBasedOnActorForwardVector(const FVector& ActorForwardVector) const;
	void SetFlipbookGetHitWithPudding(const EEnemyGetHitPudding GetHitPudding) const;
	void SetFlipbookFlashed() const;

private:
	UFUNCTION()
	void SetFlipbookToEatPudding();

	UPROPERTY(EditDefaultsOnly, Category="Enemy Look")
	UPXEnemyDA* EnemyDA{nullptr};

	UPROPERTY()
	UPaperFlipbookComponent* FlipbookComponent{nullptr};
};
