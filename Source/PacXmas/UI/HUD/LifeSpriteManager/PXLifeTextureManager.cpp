// Copyright (c) 2023 Smoking Carrots. All rights reserved.


#include "PXLifeTextureManager.h"
#include "PacXmas/GameInstance/PXGameInstance.h"
#include "PacXmas/Subsystems/ClassSubsystem/PXClassSubsystem.h"
#include "PacXmas/Utilities/CustomLogs/PXCustomLogs.h"

UTexture2D* UPXLifeTextureManager::GetLifeTexture() const
{
	if (!PXClassSubsystem)
	{
		UE_LOG(LogSubsystem, Warning, TEXT("UPXLifeTextureManager::GetLifeTexture|PXClassSubsystem is nullptr"))
		return nullptr;
	}
	if (!LifeTextureGirl)
	{
		UE_LOG(LogTexture, Warning, TEXT("UPXLifeTextureManager::GetLifeTexture|LifeTextureGirl is nullptr"))
		return nullptr;
	}
	if (!LifeTextureBoy)
	{
		UE_LOG(LogTexture, Warning, TEXT("UPXLifeTextureManager::GetLifeTexture|LifeTextureBoy is nullptr"))
		return nullptr;
	}

	const EPlayerClass PlayerClass = PXClassSubsystem->GetPlayerClass();

	switch (PlayerClass)
	{
	case EPlayerClass::Girl:
		return LifeTextureGirl;
	case EPlayerClass::Boy:
		return LifeTextureBoy;
	default:
		return nullptr;
	}
}

void UPXLifeTextureManager::InitializeClassSubsystem()
{
	if (!GetWorld())
	{
		UE_LOG(LogSubsystem, Warning, TEXT("UPXLifeTextureManager::InitializeClassSubsystem|GetWorld() is nullptr"))
		return;
	}

	const UPXGameInstance* PXGameInstance = Cast<UPXGameInstance>(GetWorld()->GetGameInstance());

	if (!PXGameInstance)
	{
		UE_LOG(LogGameInstance, Warning,
		       TEXT("UPXLifeTextureManager::InitializeClassSubsystem|PXGameInstance is nullptr"))
		return;
	}

	PXClassSubsystem = PXGameInstance->GetSubsystem<UPXClassSubsystem>();
}
