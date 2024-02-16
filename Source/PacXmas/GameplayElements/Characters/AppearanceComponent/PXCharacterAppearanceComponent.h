// Copyright (c) 2023 Smoking Carrots. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PXCharacterAppearanceComponent.generated.h"

UCLASS()
class PACXMAS_API UPXCharacterAppearanceComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPXCharacterAppearanceComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
