// Copyright (c) 2023 Smoking Carrots. All rights reserved.


#include "PXEndGameWidget.h"
#include "Components/WidgetSwitcher.h"
#include "PacXmas/UI/Menu/PXMenuManager.h"
#include "PacXmas/Utilities/CustomLogs/PXCustomLogs.h"

void UPXEndGameWidget::NativeConstruct()
{
	Super::NativeConstruct();

	InitializeMenuManager();
}

void UPXEndGameWidget::OpenStartGameWidget() const
{
	if (!MenuManager)
	{
		UE_LOG(LogMenuManager, Warning, TEXT("UPXEndGameWidget::OpenChooseNameWidget|MenuManager is nullptr"))
		return;
	}

	MenuManager->OpenStartGameWidget();
}

void UPXEndGameWidget::OpenHighscoresWidget() const
{
	if (!MenuManager)
	{
		UE_LOG(LogMenuManager, Warning, TEXT("UPXEndGameWidget::OpenHighscoresWidget|MenuManger is nullptr"))
		return;
	}

	MenuManager->OpenHighscoresWidget();
}

void UPXEndGameWidget::InitializeMenuManager()
{
	if (!MenuManagerClass)
	{
		UE_LOG(LogClass, Warning, TEXT("UPXEndGameWidget::InitializeMenuManager|MenuManagerClass is nullptr"))
		return;
	}

	MenuManager = NewObject<UPXMenuManager>(this, MenuManagerClass);

	if (!MenuManager)
	{
		UE_LOG(LogMenuManager, Warning, TEXT("UPXEndGameWidget::InitializeMenuManager|MenuManager is nullptr"))
		return;
	}

	MenuManager->InitializeWidgets();
}
