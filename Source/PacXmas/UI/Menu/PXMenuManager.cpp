// Copyright (c) 2023 Santa Claus. All rights reserved.


#include "PXMenuManager.h"
#include "PacXmas/Utilities/CustomLogs/PXCustomLogs.h"
#include "Widgets/ChooseName/PXChooseNameWidget.h"
#include "Widgets/EndGame/PXEndGameWidget.h"
#include "Widgets/Highscores/PXHighscoresWidget.h"
#include "Widgets/StartGame/PXStartGameWidget.h"

void UPXMenuManager::InitializeWidgets()
{
	StartGameWidget = InitializeWidget(StartGameWidgetClass);
	ChooseNameWidget = InitializeWidget(ChooseNameWidgetClass);
	HighscoresWidget = InitializeWidget(HighscoresWidgetClass);
	EndGameWidget = InitializeWidget(EndGameWidgetClass);
}

void UPXMenuManager::OpenStartGameWidget() const
{
	OpenWidget(StartGameWidget);
}

void UPXMenuManager::OpenChooseNameWidget() const
{
	OpenWidget(ChooseNameWidget);
}

void UPXMenuManager::OpenHighscoresWidget() const
{
	OpenWidget(HighscoresWidget);
}

void UPXMenuManager::OpenEndGameWidget() const
{
	OpenWidget(EndGameWidget);

	// todo add if to activate widget on loose and on win
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
