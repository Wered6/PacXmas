// Copyright (c) 2023 Smoking Carrots. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "PacXmas/UI/Menu/Widgets/BaseMenu/PXBaseMenuWidget.h"
#include "PXChooseClassWidget.generated.h"

class UPXGameInstance;

UCLASS()
class PACXMAS_API UPXChooseClassWidget : public UPXBaseMenuWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

public:
	UFUNCTION(BlueprintCallable)
	void PickGirl() const;
	UFUNCTION(BlueprintCallable)
	void PickBoy() const;

private:
	UPROPERTY()
	UPXGameInstance* PXGameInstance{nullptr};
};
