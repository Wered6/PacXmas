// Copyright (c) 2023 Smoking Carrots. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "PacXmas/UI/Menu/Widgets/BaseMenu/PXBaseMenuWidget.h"
#include "PXSettingsWidget.generated.h"

UCLASS()
class PACXMAS_API UPXSettingsWidget : public UPXBaseMenuWidget
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintCallable, Category="Menu|Settings|Audio")
	void OpenAudioSettingsWidget() const;

	// todo control settings
	// todo graphic settings
};
