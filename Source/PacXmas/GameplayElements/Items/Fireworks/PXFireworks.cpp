// Copyright (c) 2023 Santa Claus. All rights reserved.


#include "PXFireworks.h"
#include "PacXmas/Subsystems/FlashSubsystem/PXFlashSubsystem.h"
#include "PacXmas/Utilities/CustomLogs/PXCustomLogs.h"

void APXFireworks::BeginPlay()
{
	Super::BeginPlay();

	const UGameInstance* GameInstance = GetGameInstance();
	if (!GameInstance)
	{
		UE_LOG(LogGameInstance, Warning, TEXT("APXFireworks::BeginPlay|GameInstance is nullptr"))
		return;
	}

	FlashSubsystem = GameInstance->GetSubsystem<UPXFlashSubsystem>();
}

void APXFireworks::CollectItem(APXPlayer* PlayerCharacter)
{
	Super::CollectItem(PlayerCharacter);

	if (!FlashSubsystem)
	{
		UE_LOG(LogSubsystem, Warning, TEXT("APXFireworks::CollectItem|FlashSubsystem is nullptr"))
		return;
	}

	FlashSubsystem->CreateFlashEffect();

	// todo all devils stun with closed eyes
}
