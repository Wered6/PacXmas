// Copyright (c) 2023 Smoking Carrots. All rights reserved.


#include "PXMainMenuWidget.h"
#include "PacXmas/UI/Menu/MenuManager/PXMenuManager.h"
#include "PacXmas/Utilities/CustomLogs/PXCustomLogs.h"

void UPXMainMenuWidget::OpenChooseNameWidget() const
{
	if (!PXMenuManager)
	{
		UE_LOG(LogMenuManager, Warning, TEXT("UPXMainMenuWidget::OpenChooseNameWidget|PXMenuManager is nullptr"))
		return;
	}

	PXMenuManager->OpenChooseNameWidget();
}

void UPXMainMenuWidget::OpenHighscoresWidget() const
{
	if (!PXMenuManager)
	{
		UE_LOG(LogMenuManager, Warning, TEXT("UPXMainMenuWidget::OpenHighscoresWidget|PXMenuManager is nullptr"))
		return;
	}

	PXMenuManager->OpenHighscoresWidget();
}

void UPXMainMenuWidget::OpenSettingsWidget() const
{
	if (!PXMenuManager)
	{
		UE_LOG(LogMenuManager, Warning, TEXT("UPXMainMenuWidget::OpenSettingsWidget|PXMenuManager is nullptr"))
		return;
	}

	PXMenuManager->OpenSettingsWidget();
}
