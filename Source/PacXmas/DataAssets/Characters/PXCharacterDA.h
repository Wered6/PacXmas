// Copyright (c) 2023 Santa Claus. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PXCharacterDA.generated.h"

class UPaperFlipbook;

UCLASS()
class PACXMAS_API UPXCharacterDA : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Flipbooks")
	UPaperFlipbook* IdleFB{nullptr};
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Flipbooks")
	UPaperFlipbook* UpWalkFB{nullptr};
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Flipbooks")
	UPaperFlipbook* DownWalkFB{nullptr};
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Flipbooks")
	UPaperFlipbook* RightWalkFB{nullptr};
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Flipbooks")
	UPaperFlipbook* LeftWalkFB{nullptr};
};
