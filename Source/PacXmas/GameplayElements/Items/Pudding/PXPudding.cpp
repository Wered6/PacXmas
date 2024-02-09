// Copyright (c) 2023 Smoking Carrots. All rights reserved.


#include "PXPudding.h"
#include "PacXmas/GameplayElements/Characters/Player/PXPlayer.h"

void APXPudding::CollectItem(APXPlayer* PXPlayer)
{
	if (!PXPlayer)
	{
		UE_LOG(LogActor, Warning, TEXT("APXPudding::CollectItem|PlayerCharacter is nullptr"))
		return;
	}

	const bool bHasPudding = PXPlayer->GetHasPudding();

	if (!bHasPudding)
	{
		PXPlayer->CollectPudding();

		Super::CollectItem(PXPlayer);
	}
}
