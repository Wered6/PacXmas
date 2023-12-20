// Copyright (c) 2023 Santa Claus. All rights reserved.


#include "PXStartGameWidget.h"
#include "PacXmas/UI/Menu/PXMenuManager.h"
#include "PacXmas/Utilities/CustomLogs/PXCustomLogs.h"

void UPXStartGameWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (!MenuManagerClass)
	{
		UE_LOG(LogClass, Warning, TEXT("UPXStartGameWidget::NativeConstruct|MenuManagerClass is nullptr"))
		return;
	}

	MenuManager = NewObject<UPXMenuManager>(this, MenuManagerClass);

	if (!MenuManager)
	{
		UE_LOG(LogMenuManager, Warning, TEXT("UPXStartGameWidget::NativeConstruct|MenuManager is nullptr"))
		return;
	}

	MenuManager->InitializeWidgets();
}

void UPXStartGameWidget::OpenChooseNameWidget() const
{
	if (!MenuManager)
	{
		UE_LOG(LogMenuManager, Warning, TEXT("UPXStartGameWidget::OpenChooseNameWidget|MenuManager is nullptr"))
		return;
	}

	MenuManager->OpenChooseNameWidget();
}

void UPXStartGameWidget::OpenHighscoresWidget() const
{
	if (!MenuManager)
	{
		UE_LOG(LogMenuManager, Warning, TEXT("UPXStartGameWidget::OpenHighscoresWidget|MenuManager is nullptr"))
		return;
	}

	MenuManager->OpenHighscoresWidget();
}
