// Copyright (c) 2023 Smoking Carrots. All rights reserved.


#include "PXMenuManager.h"
#include "PacXmas/Utilities/CustomLogs/PXCustomLogs.h"
#include "Widgets/Celebration/PXCelebrationWidget.h"
#include "Widgets/ChooseClass/PXChooseClassWidget.h"
#include "Widgets/ChooseName/PXChooseNameWidget.h"
#include "Widgets/EndGame/PXEndGameWidget.h"
#include "Widgets/Highscores/PXHighscoresWidget.h"
#include "Widgets/MainMenu/PXMainMenuWidget.h"

void UPXMenuManager::InitializeWidgets()
{
	PXMainMenuWidget = InitializeWidget(PXMainMenuWidgetClass);
	ChooseNameWidget = InitializeWidget(ChooseNameWidgetClass);
	ChooseClassWidget = InitializeWidget(ChooseClassWidgetClass);
	HighscoresWidget = InitializeWidget(HighscoresWidgetClass);
	EndGameWidget = InitializeWidget(EndGameWidgetClass);
	CelebrationWidget = InitializeWidget(CelebrationWidgetClass);
}

void UPXMenuManager::OpenStartGameWidget() const
{
	OpenWidget(PXMainMenuWidget);
}

void UPXMenuManager::OpenChooseNameWidget() const
{
	OpenWidget(ChooseNameWidget);
}

void UPXMenuManager::OpenChooseClassWidget() const
{
	OpenWidget(ChooseClassWidget);
}

void UPXMenuManager::OpenHighscoresWidget() const
{
	OpenWidget(HighscoresWidget);
}

void UPXMenuManager::OpenEndGameWidget() const
{
	OpenWidget(EndGameWidget);
}

void UPXMenuManager::OpenCelebrationWidget() const
{
	OpenWidget(CelebrationWidget);
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
