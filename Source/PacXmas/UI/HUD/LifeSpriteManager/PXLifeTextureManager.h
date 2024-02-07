// Copyright (c) 2023 Smoking Carrots. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "PXLifeTextureManager.generated.h"

class UPXClassSubsystem;

UCLASS(Blueprintable)
class PACXMAS_API UPXLifeTextureManager : public UObject
{
	GENERATED_BODY()

public:
	UTexture2D* GetLifeTexture() const;

private:
	void InitializeClassSubsystem();

	UPROPERTY(EditDefaultsOnly, Category="Life Textures|Girl")
	UTexture2D* LifeTextureGirl{nullptr};
	UPROPERTY(EditDefaultsOnly, Category="Life Textures|Boy")
	UTexture2D* LifeTextureBoy{nullptr};

	UPROPERTY()
	UPXClassSubsystem* PXClassSubsystem{nullptr};
};
