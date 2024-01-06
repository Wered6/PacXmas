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

	void ActiveWonGameWidget() const;
	void ActiveLostGameWidget() const;

protected:
	UFUNCTION(BlueprintCallable, Category="Menu|Choose Name")
	void OpenChooseNameWidget() const;
	UFUNCTION(BlueprintCallable, Category="Menu|Highscores")
	void OpenHighscoresWidget() const;
	
private:
	void InitializeWidgetSwitcher();
	void InitializeMenuManager();

	UPROPERTY()
	UWidgetSwitcher* WidgetSwitcher{nullptr};

	UPROPERTY()
	UCanvasPanel* WonGameWidget{nullptr};
	UPROPERTY()
	UCanvasPanel* LostGameWidget{nullptr};

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UPXMenuManager> MenuManagerClass;
	UPROPERTY()
	UPXMenuManager* MenuManager{nullptr};
};
