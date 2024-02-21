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
	// The requested audio is already playing
	if (AudioComponent && AudioComponent->GetSound() == Audio)
	{
		return;
	}

	// Stop the currently playing sound as it's different from the requested one
	if (AudioComponent)
	{
		AudioComponent->Stop();
		AudioComponent = nullptr;
	}

	// Spawn and play the new sound
	AudioComponent = UGameplayStatics::SpawnSound2D(this, Audio, 1, 1, 0, nullptr, bPersist);
	AudioComponent->Play();
}
