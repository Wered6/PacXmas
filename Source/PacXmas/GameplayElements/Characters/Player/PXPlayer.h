// Copyright (c) 2023 Santa Claus. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PXPlayer.generated.h"

class UPXGirlDA;
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
	virtual void Tick(float DeltaSeconds) override;

	void MoveHorizontal(const float Value);
	void MoveVertical(const float Value);

private:
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* CollisionComp{nullptr};
	UPROPERTY(VisibleAnywhere)
	UFloatingPawnMovement* FloatingPawnMovement{nullptr};
	UPROPERTY(VisibleAnywhere)
	UPaperFlipbookComponent* Flipbook{nullptr};

	UPROPERTY(EditAnywhere, Category="Flipbook")
	UPXGirlDA* GirlDA{nullptr};
};
