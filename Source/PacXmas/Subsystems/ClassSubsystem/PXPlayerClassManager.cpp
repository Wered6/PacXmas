// Copyright (c) 2023 Smoking Carrots. All rights reserved.


#include "PXPlayerClassManager.h"
#include "PXClassSubsystem.h"

TSubclassOf<APXPlayer> UPXPlayerClassManager::GetPlayerClass(const EPlayerClass PlayerClass) const
{
	switch (PlayerClass)
	{
	case EPlayerClass::Boy:
		{
			return PXBoyClass;
		}
	case EPlayerClass::Girl:
		{
			return PXGirlClass;
		}
	default:
		{
			return nullptr;
		}
	}
}
