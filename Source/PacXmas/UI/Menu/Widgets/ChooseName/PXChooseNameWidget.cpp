// Copyright (c) 2023 Smoking Carrots. All rights reserved.


#include "PXChooseNameWidget.h"
#include "PacXmas/UI/Menu/MenuManager/PXMenuManager.h"
#include "PacXmas/Utilities/CustomLogs/PXCustomLogs.h"

void UPXChooseNameWidget::OpenChooseClassWidget() const
{
	if (!PXMenuManager)
	{
		UE_LOG(LogMenuManager, Warning, TEXT("UPXChooseNameWidget::OpenChooseClassWidget|PXMenuManager is nullptr"))
		return;
	}

	PXMenuManager->OpenChooseClassWidget();
}
