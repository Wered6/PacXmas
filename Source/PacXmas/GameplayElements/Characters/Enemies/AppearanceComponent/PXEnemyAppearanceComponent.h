// Copyright (c) 2023 Smoking Carrots. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "PacXmas/GameplayElements/Characters/AppearanceComponent/PXCharacterAppearanceComponent.h"
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
class PACXMAS_API UPXEnemyAppearanceComponent : public UPXCharacterAppearanceComponent
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	void SetFlipbookGetHitWithPudding(const EEnemyGetHitPudding GetHitPudding) const;
	void SetFlipbookFlashed() const;

private:
	UFUNCTION()
	void SetFlipbookToEatPudding();

	UPROPERTY(EditDefaultsOnly, Category="Enemy Look")
	UPXEnemyDA* EnemyDA{nullptr};
};
