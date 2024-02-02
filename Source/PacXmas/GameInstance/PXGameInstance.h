// Copyright (c) 2023 Smoking Carrots. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "PXGameInstance.generated.h"

enum class EPlayerClass : uint8_t
{
	Girl,
	Boy
};

UCLASS()
class PACXMAS_API UPXGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	void SetPlayerClass(const EPlayerClass NewPlayerClass);
	EPlayerClass GetPlayerClass() const;

private:
	EPlayerClass PlayerClass;
};
