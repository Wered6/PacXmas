// Copyright (c) 2023 Smoking Carrots. All rights reserved.


#include "PXScoreSubsystem.h"

void UPXScoreSubsystem::AddScore(const int32 ScoreValue)
{
	Score += ScoreValue;
}

void UPXScoreSubsystem::SubScore(const int32 ScoreValue)
{
	Score -= ScoreValue;
}

int32 UPXScoreSubsystem::GetScore() const
{
	return Score;
}

void UPXScoreSubsystem::ResetScore()
{
	Score = 0;
}
