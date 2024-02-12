// Copyright (c) 2023 Smoking Carrots. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PXHeartTexturesDA.generated.h"

class UPXClassSubsystem;

UCLASS()
class PACXMAS_API UPXHeartTexturesDA : public UDataAsset
{
	GENERATED_BODY()

public:
	UTexture2D* GetHeartTextureGirl() const;
	UTexture2D* GetHeartTextureBoy() const;

private:
	UPROPERTY(EditDefaultsOnly)
	UTexture2D* HeartTextureGirl{nullptr};
	UPROPERTY(EditDefaultsOnly)
	UTexture2D* HeartTextureBoy{nullptr};
};
