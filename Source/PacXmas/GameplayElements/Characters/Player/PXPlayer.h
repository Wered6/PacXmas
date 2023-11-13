// Copyright (c) 2023 Santa Claus. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PacXmas/GameplayElements/Characters/PXCharacter.h"
#include "PXPlayer.generated.h"

class UPXGirlDA;
class UPaperFlipbookComponent;
class UFloatingPawnMovement;
class UBoxComponent;
class UPaperSpriteComponent;

UCLASS()
class PACXMAS_API APXPlayer : public APXCharacter
{
	GENERATED_BODY()

public:
	APXPlayer();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void MoveHorizontal(const float Value) override;
	virtual void MoveVertical(const float Value) override;

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
