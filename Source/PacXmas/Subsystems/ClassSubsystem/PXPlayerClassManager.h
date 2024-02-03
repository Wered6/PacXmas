// Copyright (c) 2023 Smoking Carrots. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "PXPlayerClassManager.generated.h"

enum class EPlayerClass : uint8_t;
class APXPlayer;

UCLASS(Blueprintable)
class PACXMAS_API UPXPlayerClassManager : public UObject
{
	GENERATED_BODY()

public:
	TSubclassOf<APXPlayer> GetPlayerClass(const EPlayerClass PlayerClass) const;

private:
	UPROPERTY(EditDefaultsOnly, Category="Class|Boy")
	TSubclassOf<APXPlayer> PXBoyClass;
	UPROPERTY(EditDefaultsOnly, Category="Class|Girl")
	TSubclassOf<APXPlayer> PXGirlClass;
};
