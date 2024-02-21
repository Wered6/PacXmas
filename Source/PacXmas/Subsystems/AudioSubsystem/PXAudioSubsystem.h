// Copyright (c) 2023 Smoking Carrots. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "PXAudioSubsystem.generated.h"

UCLASS(Blueprintable)
class PACXMAS_API UPXAudioSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	// USubsystem implementation Begin
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	// USubsystem implementation End

	UFUNCTION(BlueprintCallable, Category="Audio")
	void PlayAudio(USoundBase* Audio, const bool bPersist);
	// todo every time I enter or renter main menu it resets music
	
private:
	UPROPERTY()
	UAudioComponent* PXAudioComponent{nullptr};

	bool bInitialized{false};
};
