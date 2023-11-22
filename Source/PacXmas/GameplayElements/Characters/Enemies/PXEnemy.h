// Copyright (c) 2023 Santa Claus. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PacXmas/GameplayElements/Characters/PXCharacter.h"
#include "PXEnemy.generated.h"

class UPXEnemyBehaviorComponent;

UCLASS()
class PACXMAS_API APXEnemy : public APXCharacter
{
	GENERATED_BODY()

public:
	APXEnemy();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

public:
	FVector GetScaledBoxExtent() const;

private:
	UPROPERTY()
	UPXEnemyBehaviorComponent* BehaviorComponent{nullptr};
};
