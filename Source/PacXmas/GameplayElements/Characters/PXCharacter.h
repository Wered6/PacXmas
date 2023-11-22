// Copyright (c) 2023 Santa Claus. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PXCharacter.generated.h"

class UPaperFlipbookComponent;
class UFloatingPawnMovement;
class UBoxComponent;
class UPXCharacterDA;

UCLASS()
class PACXMAS_API APXCharacter : public APawn
{
	GENERATED_BODY()

public:
	APXCharacter();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

public:
	virtual void MoveHorizontal(const float Value);
	virtual void MoveVertical(const float Value);

protected:
	void SetFlipbookToIdle() const;

	UPROPERTY(EditDefaultsOnly)
	UFloatingPawnMovement* FloatingPawnMovement{nullptr};
	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* CollisionComponent{nullptr};

private:
	UPROPERTY(EditDefaultsOnly, Category="DataAsset|Default")
	UPXCharacterDA* CharacterDA{nullptr};
	UPROPERTY(EditDefaultsOnly)
	UPaperFlipbookComponent* FlipbookComponent{nullptr};

	const float CollisionWidth{31.f};
	const float CollisionDepth{31.f};
	const float CollisionHeight{31.f};
};
