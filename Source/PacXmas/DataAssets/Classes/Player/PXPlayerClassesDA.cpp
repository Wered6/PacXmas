// Copyright (c) 2023 Smoking Carrots. All rights reserved.


#include "PXPlayerClassesDA.h"
#include "PacXmas/Subsystems/ClassSubsystem/PXClassSubsystem.h"

TSubclassOf<APXPlayer> UPXPlayerClassesDA::GetPlayerClass(const EPlayerClass PlayerClass) const
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
