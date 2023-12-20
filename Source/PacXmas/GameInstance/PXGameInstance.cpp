// Copyright (c) 2023 Santa Claus. All rights reserved.


#include "PXGameInstance.h"

void UPXGameInstance::SetPlayerClass(const EPlayerClass playerClass)
{
	PlayerClass = playerClass;
}

EPlayerClass UPXGameInstance::GetPlayerClass() const
{
	return PlayerClass;
}
