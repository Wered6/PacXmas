// Copyright (c) 2023 Santa Claus. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PXBoard.generated.h"

class UPXScoreSubsystem;
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
	void FillBoard();

private:
	void CompleteLevel() const;
	
	uint8_t MusicSheetCount{0};
	
	UPROPERTY()
	UBoxComponent* CollisionComponent{nullptr};
	UPROPERTY()
	UPaperSpriteComponent* PaperSpriteComponent{nullptr};

	UPROPERTY(EditDefaultsOnly, Category="DataAsset")
	UPXBoardDA* BoardDA{nullptr};

	const float CollisionSize{31.f};

	UPROPERTY()
	UPXScoreSubsystem* PXScoreSubsystem{nullptr};
};
