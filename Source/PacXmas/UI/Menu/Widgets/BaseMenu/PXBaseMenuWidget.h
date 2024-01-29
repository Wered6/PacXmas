// Copyright (c) 2023 Smoking Carrots. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PXBaseMenuWidget.generated.h"

class UPXMenuManager;

UCLASS()
class PACXMAS_API UPXBaseMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

protected:
	UPROPERTY()
	UPXMenuManager* PXMenuManager{nullptr};

private:
	void InitializeMenuManager();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UPXMenuManager> PXMenuManagerClass;
};
