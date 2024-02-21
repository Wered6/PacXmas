// Copyright (c) 2023 Smoking Carrots. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PXBoard.generated.h"

enum class EScoreTypes;
class UPXLevelSubsystem;
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
	void InitializeLeveSubsystem();
	void InitializeScoreSubsystem();

	void PlayBringMusicSheetSound() const;
	
	void AddAndPopupScore(const EScoreTypes ScoreType) const;
	
	void CompleteLevel() const;

	UPROPERTY(EditDefaultsOnly, Category="Sound")
	USoundBase* BringMusicSheetSound{nullptr};
	
	uint8_t MusicSheetCount{0};
	
	UPROPERTY()
	UBoxComponent* CollisionComponent{nullptr};
	UPROPERTY()
	UPaperSpriteComponent* PaperSpriteComponent{nullptr};

	UPROPERTY(EditDefaultsOnly, Category="DataAsset")
	UPXBoardDA* BoardDA{nullptr};

	const float CollisionSize{31.f};
	
	UPROPERTY()
	UPXLevelSubsystem* PXLevelSubsystem{nullptr};
	UPROPERTY()
	UPXScoreSubsystem* PXScoreSubsystem{nullptr};
};
