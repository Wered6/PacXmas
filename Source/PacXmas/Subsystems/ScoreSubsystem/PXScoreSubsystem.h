// Copyright (c) 2023 Smoking Carrots. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "PXScoreSubsystem.generated.h"

struct FHighScoreEntry
{
	FString PlayerName;
	int32 Score;
};

UCLASS()
class PACXMAS_API UPXScoreSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	void AddScore(const int32 ScoreValue);
	void SubScore(const int32 ScoreValue);
	int32 GetScore() const;
	void ResetScore();

	void SaveHighScore();
	void LoadHighScore();

private:
	int32 Score{0};

	TArray<FHighScoreEntry> HighScores;
};
