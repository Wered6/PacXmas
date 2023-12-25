// Copyright (c) 2023 Santa Claus. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PXPlayerThrowPuddingDA.generated.h"

class UPaperFlipbook;

UCLASS()
class PACXMAS_API UPXPlayerThrowPuddingDA : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category="Throw Pudding")
	UPaperFlipbook* ThrowPuddingUp{nullptr};
	UPROPERTY(EditDefaultsOnly, Category="Throw Pudding")
	UPaperFlipbook* ThrowPuddingDown{nullptr};
	UPROPERTY(EditDefaultsOnly, Category="Throw Pudding")
	UPaperFlipbook* ThrowPuddingLeft{nullptr};
	UPROPERTY(EditDefaultsOnly, Category="Throw Pudding")
	UPaperFlipbook* ThrowPuddingRight{nullptr};
};
