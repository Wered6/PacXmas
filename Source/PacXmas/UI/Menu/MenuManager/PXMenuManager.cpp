// Copyright (c) 2023 Smoking Carrots. All rights reserved.


#include "PXMenuManager.h"
#include "PacXmas/UI/Menu/Widgets/Celebration/PXCelebrationWidget.h"
#include "PacXmas/UI/Menu/Widgets/ChooseClass/PXChooseClassWidget.h"
#include "PacXmas/UI/Menu/Widgets/ChooseName/PXChooseNameWidget.h"
#include "PacXmas/UI/Menu/Widgets/EndGame/PXEndGameWidget.h"
#include "PacXmas/UI/Menu/Widgets/Highscores/PXHighscoresWidget.h"
#include "PacXmas/UI/Menu/Widgets/MainMenu/PXMainMenuWidget.h"
#include "PacXmas/UI/Menu/Widgets/SettingsAudio/PXAudioSettingsWidget.h"
#include "PacXmas/Utilities/CustomLogs/PXCustomLogs.h"

void UPXMenuManager::OpenMainMenuWidget()
{
	PXMainMenuWidget = InitializeWidget(PXMainMenuWidgetClass);

	OpenWidget(PXMainMenuWidget);
}

void UPXMenuManager::OpenChooseNameWidget()
{
	PXChooseNameWidget = InitializeWidget(PXChooseNameWidgetClass);

	OpenWidget(PXChooseNameWidget);
}

void UPXMenuManager::OpenChooseClassWidget()
{
	PXChooseClassWidget = InitializeWidget(PXChooseClassWidgetClass);

	OpenWidget(PXChooseClassWidget);
}

void UPXMenuManager::OpenHighscoresWidget()
{
	PXHighscoresWidget = InitializeWidget(PXHighscoresWidgetClass);

	OpenWidget(PXHighscoresWidget);
}

void UPXMenuManager::OpenEndGameWidget()
{
	PXEndGameWidget = InitializeWidget(PXEndGameWidgetClass);

	OpenWidget(PXEndGameWidget);
}

void UPXMenuManager::OpenCelebrationWidget()
{
	PXCelebrationWidget = InitializeWidget(PXCelebrationWidgetClass);

	OpenWidget(PXCelebrationWidget);
}

void UPXMenuManager::OpenAudioSettingsWidget()
{
	PXAudioSettingsWidget = InitializeWidget(PXAudioSettingsWidgetClass);

	OpenWidget(PXAudioSettingsWidget);
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
