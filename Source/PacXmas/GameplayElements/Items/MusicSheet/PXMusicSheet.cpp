// Copyright (c) 2023 Smoking Carrots. All rights reserved.


#include "PXMusicSheet.h"
#include "PacXmas/GameplayElements/Characters/Player/PXPlayer.h"

void APXMusicSheet::CollectItem(APXPlayer* PXPlayer)
{
	if (!PXPlayer)
	{
		UE_LOG(LogActor, Warning, TEXT("APXMusicSheet::CollectItem|PlayerCharacter is nullptr"))
		return;
	}
	
	const bool bHasMusicSheet = PXPlayer->GetHasMusicSheet();

	if (!bHasMusicSheet)
	{
		PXPlayer->CollectMusicSheet();

		Super::CollectItem(PXPlayer);
	}
}
