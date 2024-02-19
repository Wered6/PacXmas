// Copyright (c) 2023 Smoking Carrots. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "PacXmas/GameplayElements/Characters/PXCharacter.h"
#include "PXPlayer.generated.h"

class UPXPlayerMovementComponent;
class UPXPlayerAppearanceComponent;
class APXProjectilePudding;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FShootPuddingDelegate, bool, HasMusicSheet, FVector, ActorForwardVector);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPlayerHUDUpdateDelegate);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGameOverDelegate);

UCLASS()
class PACXMAS_API APXPlayer : public APXCharacter
{
	GENERATED_BODY()

public:
	APXPlayer();

protected:
	virtual void BeginPlay() override;

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
	FShootPuddingDelegate OnShootPudding;

	uint8_t GetLives() const;
	void LooseLife();
	FGameOverDelegate OnGameOver;

	FPlayerHUDUpdateDelegate OnPlayerHUDUpdate;

private:
	// Shoot Pudding Animation End related methods
	UFUNCTION()
	void ResumeMovement();
	UFUNCTION()
	void SpawnProjectilePudding();
	void BindOnShootPuddingAnimationEndDelegate();

	void HandleGameOver() const;

	void UpdateHearts() const;

	void BecomeUntouchable();
	void BecomeTouchable();

	void ChangeLook() const;


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
	UPROPERTY()
	UPXPlayerMovementComponent* PXPlayerMovementComponent{nullptr};
};
