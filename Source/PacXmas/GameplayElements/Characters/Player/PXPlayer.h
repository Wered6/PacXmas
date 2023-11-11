// Copyright (c) 2023 Santa Claus. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PXPlayer.generated.h"

class UPaperFlipbookComponent;
class UFloatingPawnMovement;
class UBoxComponent;
class UPaperSpriteComponent;

UCLASS()
class PACXMAS_API APXPlayer : public APawn
{
	GENERATED_BODY()

public:
	APXPlayer();

protected:
	virtual void BeginPlay() override;

public:
	void MoveHorizontal(const float Value);
	void MoveVertical(const float Value);

private:
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* CollisionComp{nullptr};
	UPROPERTY(VisibleAnywhere)
	UFloatingPawnMovement* FloatingPawnMovement{nullptr};
	UPROPERTY(VisibleAnywhere)
	UPaperFlipbookComponent* FlipbookStandingIdle{nullptr};
};
