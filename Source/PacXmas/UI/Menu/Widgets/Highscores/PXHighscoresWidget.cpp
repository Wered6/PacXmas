// Copyright (c) 2023 Smoking Carrots. All rights reserved.


#include "PXHighscoresWidget.h"
#include "PacXmas/UI/Menu/MenuManager/PXMenuManager.h"
#include "PacXmas/Utilities/CustomLogs/PXCustomLogs.h"

void UPXHighscoresWidget::OpenMainMenuWidget() const
{
	if (!PXMenuManager)
	{
		UE_LOG(LogMenuManager, Warning, TEXT("UPXHighscoresWidget::OpenMainMenuWidget|PXMenuManager is nullptr"))
		return;
	}

	PXMenuManager->OpenMainMenuWidget();
}
