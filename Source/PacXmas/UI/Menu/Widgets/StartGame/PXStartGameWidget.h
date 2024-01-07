// Copyright (c) 2023 Smoking Carrots. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PXStartGameWidget.generated.h"

class UPXMenuManager;

UCLASS()
class PACXMAS_API UPXStartGameWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

protected:
	UFUNCTION(BlueprintCallable, Category="Menu|Choose Name")
	void OpenChooseNameWidget() const;
	UFUNCTION(BlueprintCallable, Category="Menu|Highscores")
	void OpenHighscoresWidget() const;

private:
	void InitializeMenuManager();
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UPXMenuManager> MenuManagerClass;
	UPROPERTY()
	UPXMenuManager* MenuManager{nullptr};
};
