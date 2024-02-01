// Copyright (c) 2023 Smoking Carrots. All rights reserved.


#include "PXAudioSubsystem.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PacXmas/Utilities/CustomLogs/PXCustomLogs.h"

void UPXAudioSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	check(!bInitialized);
	bInitialized = true;
}

void UPXAudioSubsystem::Deinitialize()
{
	check(bInitialized);
	bInitialized = false;
}

void UPXAudioSubsystem::PlayAudio(USoundBase* Audio, const bool bPersist)
{
	if (!Audio)
	{
		UE_LOG(LogSound, Warning, TEXT("UPXAudioSubsystem::PlayAudio|Audio is nullptr"))
		return;
	}

	if (PXAudioComponent)
	{
		PXAudioComponent->Stop();
	}

	PXAudioComponent = UGameplayStatics::SpawnSound2D(this, Audio, 1, 1, 0, nullptr, bPersist);
	PXAudioComponent->Play();
}
