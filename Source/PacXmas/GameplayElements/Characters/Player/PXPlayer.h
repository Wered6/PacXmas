// Copyright (c) 2023 Santa Claus. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "PacXmas/GameplayElements/Characters/PXCharacter.h"
#include "PXPlayer.generated.h"

class UPXPlayerAppearanceComponent;
class APXProjectilePudding;

UCLASS()
class PACXMAS_API APXPlayer : public APXCharacter
{
	GENERATED_BODY()

public:
	APXPlayer();

public:
	virtual void Tick(float DeltaSeconds) override;

public:
	virtual void MoveHorizontal(const float Value);
	virtual void MoveVertical(const float Value);

	void CollectMusicSheet();
	void DropMusicSheet();
	bool GetHasMusicSheet() const;

	void CollectPudding();
	void ShootPudding();
	bool GetHasPudding() const;

	uint8_t GetLives() const;
	void LooseLife();

private:
	void GameOver() const;
	
	void HeartBlinking() const;

	void BecomeUntouchable();
	void BecomeTouchable();

	void ChangeLook() const;

	void SpawnProjectilePudding() const;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<APXProjectilePudding> ProjectileClass{nullptr};

	bool bHasPudding{false};
	bool bHasMusicSheet{false};

	uint8_t Lives{3};

	bool bIsUntouchable{false};
	float UntouchableDuration{1.2f};
	FTimerHandle UntouchableTimerHandle;

	UPROPERTY(EditDefaultsOnly)
	UPXPlayerAppearanceComponent* PXPlayerAppearanceComponent{nullptr};
};
