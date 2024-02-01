// Copyright (c) 2023 Smoking Carrots. All rights reserved.


#include "PXSettingsWidget.h"
#include "PacXmas/UI/Menu/MenuManager/PXMenuManager.h"
#include "PacXmas/Utilities/CustomLogs/PXCustomLogs.h"

void UPXSettingsWidget::OpenAudioSettingsWidget() const
{
	if (!PXMenuManager)
	{
		UE_LOG(LogMenuManager, Warning, TEXT("UPXSettingsWidget::OpenAudioSettings|PXMenuManager is nullptr"))
		return;
	}

	PXMenuManager->OpenAudioSettingsWidget();
}
