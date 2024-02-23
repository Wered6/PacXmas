// Copyright (c) 2023 Smoking Carrots. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PXHighscoresWidget.generated.h"

class UVerticalBox;
class UPXScoreSubsystem;

UCLASS()
class PACXMAS_API UPXHighscoresWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativePreConstruct() override;

private:
	void InitializeScoreSubsystem();

	UFUNCTION(BlueprintCallable)
	void UpdateHighscoresWidget() const;

	UPROPERTY(meta=(BindWidget))
	UVerticalBox* Nicknames{nullptr};
	UPROPERTY(meta=(BindWidget))
	UVerticalBox* Highscores{nullptr};

	UPROPERTY()
	UPXScoreSubsystem* PXScoreSubsystem{nullptr};
};
