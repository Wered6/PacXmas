// Copyright (c) 2023 Smoking Carrots. All rights reserved.


#include "PXClassSubsystem.h"

void UPXClassSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	check(!bInitialized);
	bInitialized = true;
}

void UPXClassSubsystem::Deinitialize()
{
	check(bInitialized);
	bInitialized = false;
}

void UPXClassSubsystem::SetPlayerClass(const EPlayerClass NewPlayerClass)
{
	PlayerClass = NewPlayerClass;
}

EPlayerClass UPXClassSubsystem::GetPlayerClass() const
{
	return PlayerClass;
}
