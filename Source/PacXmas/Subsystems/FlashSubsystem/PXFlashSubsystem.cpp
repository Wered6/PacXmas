// Copyright (c) 2023 Smoking Carrots. All rights reserved.


#include "PXFlashSubsystem.h"
#include "EngineUtils.h"
#include "Engine/PostProcessVolume.h"

ETickableTickType UPXFlashSubsystem::GetTickableTickType() const
{
	// By default (if the child class doesn't override GetTickableTickType), don't let CDOs ever tick:
	return IsTemplate() ? ETickableTickType::Never : FTickableGameObject::GetTickableTickType();
}

bool UPXFlashSubsystem::IsAllowedToTick() const
{
	return !IsTemplate() && bInitialized;
}

void UPXFlashSubsystem::Tick(float DeltaTime)
{
	if (PostProcessVolume)
	{
		CurrentBloomIntensity = FMath::FInterpTo(CurrentBloomIntensity, TargetBloomIntensity, DeltaTime,
		                                         BloomIntensityTransitionSpeed);
		PostProcessVolume->Settings.BloomIntensity = CurrentBloomIntensity;
	}
}

TStatId UPXFlashSubsystem::GetStatId() const
{
	RETURN_QUICK_DECLARE_CYCLE_STAT(UPXFlashSubsystem, STATGROUP_Tickables);
}

void UPXFlashSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	check(!bInitialized);
	bInitialized = true;
}

void UPXFlashSubsystem::Deinitialize()
{
	check(bInitialized);
	bInitialized = false;
}

void UPXFlashSubsystem::CreateFlashEffect()
{
	InitializePostProcessVolume();
	
	// Check if the timer is already active and reset/extend it
	if (GetWorld()->GetTimerManager().IsTimerActive(TimerHandle))
	{
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
	}

	TargetBloomIntensity = 8.f;

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UPXFlashSubsystem::ResetBloomIntensity, FlashDuration);
}

void UPXFlashSubsystem::InitializePostProcessVolume()
{
	for (TActorIterator<APostProcessVolume> It(GetWorld()); It; ++It)
	{
		APostProcessVolume* FoundPostProcessVolume = *It;
		if (IsValid(FoundPostProcessVolume))
		{
			PostProcessVolume = FoundPostProcessVolume;
			CurrentBloomIntensity = BaseBloomIntensity;
			TargetBloomIntensity = BaseBloomIntensity;
			bPostProcessVolumeInitialized = true;
			break;
		}
	}
}

void UPXFlashSubsystem::ResetBloomIntensity()
{
	TargetBloomIntensity = BaseBloomIntensity;
}
