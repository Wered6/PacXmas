// Copyright (c) 2023 Santa Claus. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PXChooseNameWidget.generated.h"

class UPXMenuManager;

UCLASS()
class PACXMAS_API UPXChooseNameWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

public:
	UFUNCTION(BlueprintCallable, Category="Menu|Choose Class")
	void OpenChooseClassWidget() const;

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UPXMenuManager> MenuManagerClass;
	UPROPERTY()
	UPXMenuManager* MenuManager{nullptr};
};
