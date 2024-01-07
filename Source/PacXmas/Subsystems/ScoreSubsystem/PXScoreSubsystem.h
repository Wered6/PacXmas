// Copyright (c) 2023 Smoking Carrots. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "PXScoreSubsystem.generated.h"

USTRUCT(BlueprintType)
struct FHighScoreEntry
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	FString PlayerName;
	UPROPERTY(BlueprintReadOnly)
	int32 Score;

	// Overload the less-than operator for Sort function
	FORCEINLINE bool operator<(const FHighScoreEntry& Other) const
	{
		return Score > Other.Score;
	}
};

UCLASS()
class PACXMAS_API UPXScoreSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	// USubsystem implementation Begin
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	// USubsystem implementation End

	UFUNCTION(BlueprintCallable)
	TArray<FHighScoreEntry> GetHighscores() const;

	UFUNCTION(BlueprintCallable)
	void SetPlayerName(FString NewPlayerName);

	void AddScore(const int32 ScoreValue);
	void SubScore(const int32 ScoreValue);
	int32 GetScore() const;
	void ResetScore();

	void UpdateHighScores();

private:
	void SaveHighScores() const;
	void LoadHighScores();

	FString PlayerName;
	int32 Score{0};

	TArray<FHighScoreEntry> HighScores;

	bool bInitialized{false};
};
