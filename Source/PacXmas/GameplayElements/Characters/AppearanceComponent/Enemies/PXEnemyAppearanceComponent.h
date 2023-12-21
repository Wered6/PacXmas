// Copyright (c) 2023 Santa Claus. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "PacXmas/GameplayElements/Characters/AppearanceComponent/PXAppearanceComponent.h"
#include "PXEnemyAppearanceComponent.generated.h"

class UPXDevilDA;

enum class EEnemyGetHitPudding : uint8
{
	Up,
	Down,
	Left,
	Right
};

UCLASS()
class PACXMAS_API UPXEnemyAppearanceComponent : public UPXAppearanceComponent
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	void SetFlipbookGetHitWithPudding(const EEnemyGetHitPudding GetHitPudding) const;

private:
	UFUNCTION()
	void SetFlipbookToEatPudding();

	UPROPERTY(EditDefaultsOnly, Category="DataAssets|Pudding")
	UPXDevilDA* DevilPuddingDA{nullptr};
};
