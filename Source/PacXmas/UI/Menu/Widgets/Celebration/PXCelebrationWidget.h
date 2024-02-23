// Copyright (c) 2023 Smoking Carrots. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PXCelebrationWidget.generated.h"

class UTextBlock;
class UPXScoreSubsystem;

UCLASS()
class PACXMAS_API UPXCelebrationWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativePreConstruct() override;

private:
	void InitializeScoreSubsystem();

	UFUNCTION(BlueprintCallable)
	void SetScoreText() const;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* Score{nullptr};
	
	UPROPERTY()
	UPXScoreSubsystem* PXScoreSubsystem{nullptr};
};
