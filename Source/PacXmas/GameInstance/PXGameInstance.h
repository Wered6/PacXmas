// Copyright (c) 2023 Santa Claus. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "PXGameInstance.generated.h"

UENUM(BlueprintType)
enum class EPlayerClass : uint8
{
	Girl UMETA(DisplayName = "Girl"),
	Boy UMETA(DisplayName = "Boy")
};

UCLASS()
class PACXMAS_API UPXGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	void SetPlayerClass(const EPlayerClass playerClass);
	EPlayerClass GetPlayerClass() const;

private:
	EPlayerClass PlayerClass;
};
