// Copyright (c) 2023 Smoking Carrots. All rights reserved.


#include "PXScoreSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "PacXmas/SaveGame/HighScores/PXHighScoresSaveGame.h"

void UPXScoreSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	check(!bInitialized);
	bInitialized = true;

	LoadHighScores();
}

void UPXScoreSubsystem::Deinitialize()
{
	check(bInitialized);
	bInitialized = false;
}

TArray<FHighScoreEntry> UPXScoreSubsystem::GetHighscores() const
{
	return HighScores;
}

void UPXScoreSubsystem::SetPlayerName(FString NewPlayerName)
{
	PlayerName = NewPlayerName;
}

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

void UPXScoreSubsystem::UpdateHighScores()
{
	if (!PlayerName.IsEmpty())
	{
		FHighScoreEntry NewHighScoreEntry;
		NewHighScoreEntry.PlayerName = PlayerName;
		NewHighScoreEntry.Score = Score;

		HighScores.Add(NewHighScoreEntry);
		HighScores.Sort();

		if (HighScores.Num() > 10)
		{
			HighScores.RemoveAt(10);
		}

		SaveHighScores();
	}
}

bool UPXScoreSubsystem::IsHighScoreBeaten()
{
	if (HighScores.Num() > 0)
	{
		return Score > HighScores[0].Score;
	}

	return true;
}

void UPXScoreSubsystem::SaveHighScores() const
{
	UPXHighScoresSaveGame* PXHighScoresSaveGameInstance = Cast<UPXHighScoresSaveGame>(
		UGameplayStatics::CreateSaveGameObject(UPXHighScoresSaveGame::StaticClass()));

	if (PXHighScoresSaveGameInstance)
	{
		PXHighScoresSaveGameInstance->HighScores = HighScores;
		UGameplayStatics::SaveGameToSlot(PXHighScoresSaveGameInstance, TEXT("HighScores"), 0);
	}
}

void UPXScoreSubsystem::LoadHighScores()
{
	if (UGameplayStatics::DoesSaveGameExist(TEXT("HighScores"), 0))
	{
		const UPXHighScoresSaveGame* PXHighScoresLoadGameInstance = Cast<UPXHighScoresSaveGame>(
			UGameplayStatics::LoadGameFromSlot(TEXT("HighScores"), 0));

		if (PXHighScoresLoadGameInstance)
		{
			HighScores = PXHighScoresLoadGameInstance->HighScores;
		}
	}
}
