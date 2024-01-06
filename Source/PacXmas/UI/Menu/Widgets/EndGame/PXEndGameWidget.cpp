// Copyright (c) 2023 Smoking Carrots. All rights reserved.


#include "PXEndGameWidget.h"
#include "Components/CanvasPanel.h"
#include "Components/WidgetSwitcher.h"
#include "PacXmas/UI/Menu/PXMenuManager.h"
#include "PacXmas/Utilities/CustomLogs/PXCustomLogs.h"

void UPXEndGameWidget::NativeConstruct()
{
	Super::NativeConstruct();

	InitializeWidgetSwitcher();
	InitializeMenuManager();
}

void UPXEndGameWidget::ActiveWonGameWidget() const
{
	if (!WidgetSwitcher)
	{
		UE_LOG(LogWidget, Warning, TEXT("UPXEndGameWidget::ActiveWonGameWidget|WidgetSwitcher is nullptr"))
		return;
	}
	if (!WonGameWidget)
	{
		UE_LOG(LogWidget, Warning, TEXT("UPXEndGameWidget::ActiveWonGameWidget|WonGameWidget is nullptr"))
		return;
	}

	WidgetSwitcher->SetActiveWidget(WonGameWidget);
}

void UPXEndGameWidget::ActiveLostGameWidget() const
{
	if (!WidgetSwitcher)
	{
		UE_LOG(LogWidget, Warning, TEXT("UPXEndGameWidget::ActiveLostGameWidget|WidgetSwitcher is nullptr"))
		return;
	}
	if (!LostGameWidget)
	{
		UE_LOG(LogWidget, Warning, TEXT("UPXEndGameWidget::ActiveLostGameWidget|LostGameWidget is nullptr"))
		return;
	}

	WidgetSwitcher->SetActiveWidget(LostGameWidget);
}

void UPXEndGameWidget::OpenChooseNameWidget() const
{
	if (!MenuManager)
	{
		UE_LOG(LogMenuManager, Warning, TEXT("UPXEndGameWidget::OpenChooseNameWidget|MenuManager is nullptr"))
		return;
	}

	MenuManager->OpenChooseNameWidget();
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

void UPXEndGameWidget::InitializeWidgetSwitcher()
{
	WidgetSwitcher = Cast<UWidgetSwitcher>(GetWidgetFromName(TEXT("WidgetSwitcher0")));

	WonGameWidget = Cast<UCanvasPanel>(GetWidgetFromName(TEXT("WonGameWidget")));
	LostGameWidget = Cast<UCanvasPanel>(GetWidgetFromName(TEXT("LostGameWidget")));
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
