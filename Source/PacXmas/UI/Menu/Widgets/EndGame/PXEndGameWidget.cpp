// Copyright (c) 2023 Smoking Carrots. All rights reserved.


#include "PXEndGameWidget.h"
#include "PacXmas/UI/Menu/MenuManager/PXMenuManager.h"
#include "PacXmas/Utilities/CustomLogs/PXCustomLogs.h"

void UPXEndGameWidget::OpenMainMenuWidget() const
{
	if (!PXMenuManager)
	{
		UE_LOG(LogMenuManager, Warning, TEXT("UPXEndGameWidget::OpenMainMenuWidget|PXMenuManager is nullptr"))
		return;
	}

	PXMenuManager->OpenMainMenuWidget();
}

void UPXEndGameWidget::OpenHighscoresWidget() const
{
	if (!PXMenuManager)
	{
		UE_LOG(LogMenuManager, Warning, TEXT("UPXEndGameWidget::OpenHighscoresWidget|PXMenuManager is nullptr"))
		return;
	}

	PXMenuManager->OpenHighscoresWidget();
}
