// Copyright (c) 2023 Smoking Carrots. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PXBlockEnemyVolume.generated.h"

class UBoxComponent;

UCLASS()
class PACXMAS_API APXBlockEnemyVolume : public AActor
{
	GENERATED_BODY()

public:
	APXBlockEnemyVolume();
	
private:
	UPROPERTY()
	UBoxComponent* CollisionComponent{nullptr};

	float CollisionSize{32.f};
};
