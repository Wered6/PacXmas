// Copyright (c) 2023 Santa Claus. All rights reserved.


#include "PXChooseNameWidget.h"
#include "PacXmas/UI/Menu/PXMenuManager.h"
#include "PacXmas/Utilities/CustomLogs/PXCustomLogs.h"

void UPXChooseNameWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (!MenuManagerClass)
	{
		UE_LOG(LogClass, Warning, TEXT("UPXChooseNameWidget::NativeConstruct|MenuManagerClass is nullptr"))
		return;
	}

	MenuManager = NewObject<UPXMenuManager>(this, MenuManagerClass);

	if (!MenuManager)
	{
		UE_LOG(LogMenuManager, Warning, TEXT("UPXChooseNameWidget::NativeConstruct|MenuManager is nullptr"))
		return;
	}

	MenuManager->InitializeWidgets();
}

void UPXChooseNameWidget::OpenChooseClassWidget() const
{
	if (!MenuManager)
	{
		UE_LOG(LogMenuManager, Warning, TEXT("UPXChooseNameWidget::OpenChooseClassWidget|MenuManager is nullptr"))
		return;
	}

	MenuManager->OpenChooseClassWidget();
}
