// Copyright (c) 2023 Smoking Carrots. All rights reserved.


#include "PXCelebrationWidget.h"
#include "PacXmas/UI/Menu/PXMenuManager.h"
#include "PacXmas/Utilities/CustomLogs/PXCustomLogs.h"


void UPXCelebrationWidget::NativeConstruct()
{
	Super::NativeConstruct();

	InitializeMenuManager();

	if (!MenuManager)
	{
		UE_LOG(LogMenuManager, Warning, TEXT("UPXCelebrationWidget::NativeConstruct|MenuManager is nullptr"))
		return;
	}

	MenuManager->InitializeWidgets();
}

void UPXCelebrationWidget::OpenStartGameWidget() const
{
	if (!MenuManager)
	{
		UE_LOG(LogMenuManager, Warning, TEXT("UPXCelebrationWidget::OpenStartGameWidget|MenuManager is nullptr"))
		return;
	}

	MenuManager->OpenStartGameWidget();
}

void UPXCelebrationWidget::InitializeMenuManager()
{
	if (!MenuManagerClass)
	{
		UE_LOG(LogClass, Warning, TEXT("UPXCelebrationWidget::InitializeMenuManager|MenuManagerClass is nullptr"))
		return;
	}

	MenuManager = NewObject<UPXMenuManager>(this, MenuManagerClass);
}
