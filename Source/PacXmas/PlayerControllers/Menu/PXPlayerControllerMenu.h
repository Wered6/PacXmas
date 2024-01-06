// Copyright (c) 2023 Smoking Carrots. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PXPlayerControllerMenu.generated.h"

UCLASS()
class PACXMAS_API APXPlayerControllerMenu : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
};
