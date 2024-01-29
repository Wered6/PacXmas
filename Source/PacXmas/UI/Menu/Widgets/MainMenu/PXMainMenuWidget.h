// Copyright (c) 2023 Smoking Carrots. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PXMainMenuWidget.generated.h"

class UPXMenuManager;

UCLASS()
class PACXMAS_API UPXMainMenuWidget : public UUserWidget
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
	TSubclassOf<UPXMenuManager> PXMenuManagerClass;
	UPROPERTY()
	UPXMenuManager* PXMenuManager{nullptr};
};
