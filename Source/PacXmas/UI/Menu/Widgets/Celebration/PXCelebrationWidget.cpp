// Copyright (c) 2023 Smoking Carrots. All rights reserved.


#include "PXCelebrationWidget.h"
#include "PacXmas/UI/Menu/MenuManager/PXMenuManager.h"
#include "PacXmas/Utilities/CustomLogs/PXCustomLogs.h"

void UPXCelebrationWidget::OpenMainMenuWidget() const
{
	if (!PXMenuManager)
	{
		UE_LOG(LogMenuManager, Warning, TEXT("UPXCelebrationWidget::OpenMainMenuWidget|PXMenuManager is nullptr"))
		return;
	}

	PXMenuManager->OpenMainMenuWidget();
}
