// Copyright (c) 2023 Santa Claus. All rights reserved.


#include "PXPudding.h"

#include "PacXmas/GameplayElements/Characters/Player/PXPlayer.h"

void APXPudding::CollectItem(APXPlayer* PlayerCharacter)
{
	PlayerCharacter->CollectPudding();

	Super::CollectItem(PlayerCharacter);
}
