// Copyright (c) 2023 Smoking Carrots. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "PacXmas/UI/Menu/Widgets/BaseMenu/PXBaseMenuWidget.h"
#include "PXChooseNameWidget.generated.h"

class UPXMenuManager;

UCLASS()
class PACXMAS_API UPXChooseNameWidget : public UPXBaseMenuWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="Menu|Choose Class")
	void OpenChooseClassWidget() const;
	// todo rewrite logic  of choosing name into c++
};
