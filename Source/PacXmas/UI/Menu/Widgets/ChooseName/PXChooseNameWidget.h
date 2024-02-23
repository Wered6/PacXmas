// Copyright (c) 2023 Smoking Carrots. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PXChooseNameWidget.generated.h"

class UPXScoreSubsystem;
class UEditableText;

UCLASS()
class PACXMAS_API UPXChooseNameWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

private:
	void InitializeScoreSubsystem();

	UFUNCTION(BlueprintCallable)
	UPARAM(DisplayName="bSucceeded")
	bool SetPlayerName(const bool bIsCommitted) const;

	bool IsNicknameMinLen() const;

	uint8_t MinNicknameLen{3};

	UPROPERTY(meta=(BindWidget))
	UEditableText* Nickname{nullptr};

	UPROPERTY()
	UPXScoreSubsystem* PXScoreSubsystem{nullptr};
};
