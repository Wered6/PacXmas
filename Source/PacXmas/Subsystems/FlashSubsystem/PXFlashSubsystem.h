// Copyright (c) 2023 Santa Claus. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "PXFlashSubsystem.generated.h"

class APostProcessVolume;

UCLASS()
class PACXMAS_API UPXFlashSubsystem : public UGameInstanceSubsystem, public FTickableGameObject
{
	GENERATED_BODY()

public:
	// FTickableGameObject implementation Begin
	virtual UWorld* GetTickableGameObjectWorld() const override { return GetWorld(); };
	virtual ETickableTickType GetTickableTickType() const override;
	virtual bool IsAllowedToTick() const override;
	virtual void Tick(float DeltaTime) override;
	virtual TStatId GetStatId() const override;
	// FTickableGameObject implementation End

	// USubsystem implementation Begin
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	// USubsystem implementation End

	bool IsInitialized() const { return bInitialized; }

public:
	void CreateFlashEffect();

private:
	void InitializePostProcessVolume();

	void ResetBloomIntensity();

	FTimerHandle TimerHandle;

	UPROPERTY()
	APostProcessVolume* PostProcessVolume{nullptr};

	float BaseBloomIntensity{0.f};
	float TargetBloomIntensity{0.f};
	float CurrentBloomIntensity{0.f};
	float BloomIntensityTransitionSpeed{5.f};
	float FlashDuration{0.2f};

	bool bInitialized{false};
	bool bPostProcessVolumeInitialized{false};
};
