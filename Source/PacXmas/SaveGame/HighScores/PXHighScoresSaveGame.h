// Copyright (c) 2023 Smoking Carrots. All rights reserved.

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "PXHighScoresSaveGame.generated.h"

struct FHighScoreEntry;

UCLASS()
class PACXMAS_API UPXHighScoresSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	TArray<FHighScoreEntry> HighScores;
};
