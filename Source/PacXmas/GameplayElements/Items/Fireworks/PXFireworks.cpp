// Copyright (c) 2023 Santa Claus. All rights reserved.


#include "PXFireworks.h"

void APXFireworks::CollectItem(APXPlayer* PlayerCharacter)
{
	Super::CollectItem(PlayerCharacter);

	UE_LOG(LogTemp, Warning, TEXT("It is Fireworks!"))
}
