// Copyright (c) 2023 Santa Claus. All rights reserved.


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

	TargetBloomIntensity = 8.f;
	constexpr float FlashDuration{2.f};

	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this]()
	{
		TargetBloomIntensity = BaseBloomIntensity;
	}, FlashDuration, false);
}

void UPXFlashSubsystem::InitializePostProcessVolume()
{
	for (TActorIterator<APostProcessVolume> It(GetWorld()); It; ++It)
	{
		APostProcessVolume* PPV = *It;
		if (IsValid(PPV))
		{
			PostProcessVolume = PPV;
			BaseBloomIntensity = PostProcessVolume->Settings.BloomIntensity;
			CurrentBloomIntensity = BaseBloomIntensity;
			TargetBloomIntensity = BaseBloomIntensity;
			break;
		}
	}
}
