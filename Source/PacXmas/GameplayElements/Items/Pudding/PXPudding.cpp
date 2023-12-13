// Copyright (c) 2023 Santa Claus. All rights reserved.


#include "PXPudding.h"
#include "PacXmas/GameplayElements/Characters/Player/PXPlayer.h"

void APXPudding::CollectItem(APXPlayer* PlayerCharacter)
{
	if (!PlayerCharacter)
	{
		UE_LOG(LogActor, Warning, TEXT("APXPudding::CollectItem|PlayerCharacter is nullptr"))
		return;
	}

	const bool bHasPudding = PlayerCharacter->GetHasPudding();

	if (!bHasPudding)
	{
		PlayerCharacter->CollectPudding();

		Super::CollectItem(PlayerCharacter);
	}
}
