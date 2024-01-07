// Copyright (c) 2023 Smoking Carrots. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PXEndGameWidget.generated.h"

class UPXMenuManager;
class UCanvasPanel;
class UWidgetSwitcher;

UCLASS()
class PACXMAS_API UPXEndGameWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

protected:
	UFUNCTION(BlueprintCallable, Category="Menu|Choose Name")
	void OpenStartGameWidget() const;
	UFUNCTION(BlueprintCallable, Category="Menu|HighScores")
	void OpenHighscoresWidget() const;

private:
	void InitializeMenuManager();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UPXMenuManager> MenuManagerClass;
	UPROPERTY()
	UPXMenuManager* MenuManager{nullptr};
};
