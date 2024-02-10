// Copyright (c) 2023 Smoking Carrots. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PXPlayerClassesDA.generated.h"

enum class EPlayerClass : uint8_t;
class APXPlayer;

UCLASS()
class PACXMAS_API UPXPlayerClassesDA : public UDataAsset
{
	GENERATED_BODY()

public:
	TSubclassOf<APXPlayer> GetPlayerClass(const EPlayerClass PlayerClass) const;
	
private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<APXPlayer> PXBoyClass;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<APXPlayer> PXGirlClass;
};
