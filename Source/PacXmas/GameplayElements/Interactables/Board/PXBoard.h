// Copyright (c) 2023 Santa Claus. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PXBoard.generated.h"

class UPXBoardDA;
class UPaperSpriteComponent;
class UBoxComponent;

UCLASS()
class PACXMAS_API APXBoard : public AActor
{
	GENERATED_BODY()

public:
	APXBoard();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* CollisionComponent{nullptr};
	UPROPERTY(EditDefaultsOnly, Category="DataAsset")
	UPXBoardDA* BoardDA{nullptr};
	UPROPERTY(EditDefaultsOnly)
	UPaperSpriteComponent* PaperSpriteComponent{nullptr};

	const float CollisionWidth{31.f};
	const float CollisionDepth{31.f};
	const float CollisionHeight{31.f};
};
