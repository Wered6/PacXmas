// Copyright (c) 2023 Santa Claus. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "PXScoreSubsystem.generated.h"

UCLASS()
class PACXMAS_API UPXScoreSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	void AddScore(const int32 ScoreValue);
	void SubScore(const int32 ScoreValue);
	int32 GetScore() const;
	void ResetScore();

private:
	int32 Score{0};
};
