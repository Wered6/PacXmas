// Copyright (c) 2023 Santa Claus. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "PXGameInstance.generated.h"

enum class EPlayerClass : uint8
{
	Girl,
	Boy
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
