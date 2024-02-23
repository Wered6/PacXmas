// Copyright (c) 2023 Smoking Carrots. All rights reserved.


#include "PXMenuManager.h"
#include "PacXmas/UI/Menu/Widgets/MainMenu/PXMainMenuWidget.h"
#include "PacXmas/Utilities/CustomLogs/PXCustomLogs.h"

void UPXMenuManager::OpenMainMenuWidget()
{
	PXMainMenuWidget = InitializeWidget(PXMainMenuWidgetClass);

	OpenWidget(PXMainMenuWidget);
}


void UPXMenuManager::OpenWidget(UUserWidget* Widget) const
{
	if (!Widget)
	{
		UE_LOG(LogWidget, Warning, TEXT("UPXMenu::OpenWidget|Widget is nullptr"))
		return;
	}

	Widget->AddToViewport();
}
