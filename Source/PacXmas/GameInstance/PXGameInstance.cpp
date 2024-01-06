// Copyright (c) 2023 Smoking Carrots. All rights reserved.


#include "PXGameInstance.h"

void UPXGameInstance::SetPlayerClass(const EPlayerClass NewPlayerClass)
{
	PlayerClass = NewPlayerClass;
}

EPlayerClass UPXGameInstance::GetPlayerClass() const
{
	return PlayerClass;
}
