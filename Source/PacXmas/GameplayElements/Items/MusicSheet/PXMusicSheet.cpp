// Copyright (c) 2023 Santa Claus. All rights reserved.


#include "PXMusicSheet.h"
#include "PacXmas/GameplayElements/Characters/Player/PXPlayer.h"

void APXMusicSheet::CollectItem(APXPlayer* PlayerCharacter)
{
	PlayerCharacter->CollectMusicSheet();

	Super::CollectItem(PlayerCharacter);
}
