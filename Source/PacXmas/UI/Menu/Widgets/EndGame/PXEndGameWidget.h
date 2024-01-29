// Copyright (c) 2023 Smoking Carrots. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "PacXmas/UI/Menu/Widgets/BaseMenu/PXBaseMenuWidget.h"
#include "PXEndGameWidget.generated.h"

class UPXMenuManager;
class UCanvasPanel;
class UWidgetSwitcher;

UCLASS()
class PACXMAS_API UPXEndGameWidget : public UPXBaseMenuWidget
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintCallable, Category="Menu|Choose Name")
	void OpenMainMenuWidget() const;
	UFUNCTION(BlueprintCallable, Category="Menu|HighScores")
	void OpenHighscoresWidget() const;
};
