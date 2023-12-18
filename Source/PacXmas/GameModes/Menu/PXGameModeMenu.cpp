// Copyright (c) 2023 Santa Claus. All rights reserved.


#include "PXGameModeMenu.h"
#include "PacXmas/UI/Menu/PXMenuManager.h"
#include "PacXmas/Utilities/CustomLogs/PXCustomLogs.h"

void APXGameModeMenu::BeginPlay()
{
	Super::BeginPlay();

	if (!MenuManagerClass)
	{
		UE_LOG(LogMenuManager, Warning, TEXT("APXGameModeMenu::BeginPlay|MenuManagerClass is nullptr"))
		return;
	}

	MenuManager = NewObject<UPXMenuManager>(this, MenuManagerClass);

	if (!MenuManager)
	{
		UE_LOG(LogMenuManager, Warning, TEXT("APXGameModeMenu::BeginPlay|MenuManager is nullptr"))
		return;
	}

	MenuManager->InitializeWidgets();
	OpenAppropriateWidget();
}

void APXGameModeMenu::OpenAppropriateWidget() const
{
	// todo add some ifs if start game if won if loose
	if (!MenuManager)
	{
		UE_LOG(LogMenuManager, Warning, TEXT("APXGameModeMenu::OpenAppropriateWidget|MenuManager is nullptr"))
		return;
	}

	MenuManager->OpenStartGameWidget();
}
