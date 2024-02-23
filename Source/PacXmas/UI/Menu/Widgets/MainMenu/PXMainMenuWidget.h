// Copyright (c) 2023 Smoking Carrots. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "PacXmas/UI/Menu/Widgets/BaseMenu/PXBaseMenuWidget.h"
#include "PXMainMenuWidget.generated.h"

class UPXMenuManager;

UCLASS()
class PACXMAS_API UPXMainMenuWidget : public UPXBaseMenuWidget
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintCallable, Category="Menu|Choose Name")
	void OpenChooseNameWidget() const;
	UFUNCTION(BlueprintCallable, Category="Menu|Highscores")
	void OpenHighscoresWidget() const;
};
