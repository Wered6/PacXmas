// Copyright (c) 2023 Santa Claus. All rights reserved.


#include "PXMusicSheet.h"
#include "PacXmas/GameplayElements/Characters/Player/PXPlayer.h"

void APXMusicSheet::CollectItem(APXPlayer* PlayerCharacter)
{
	if (!PlayerCharacter)
	{
		UE_LOG(LogActor, Warning, TEXT("APXMusicSheet::CollectItem|PlayerCharacter is nullptr"))
		return;
	}
	
	const bool bHasMusicSheet = PlayerCharacter->GetHasMusicSheet();

	if (!bHasMusicSheet)
	{
		PlayerCharacter->CollectMusicSheet();

		Super::CollectItem(PlayerCharacter);
	}
}
