// Copyright (c) 2023 Santa Claus. All rights reserved.


#include "PXGameModeMenu.h"
#include "PacXmas/GameInstance/PXGameInstance.h"
#include "PacXmas/Subsystems/LevelSubsystem/PXLevelSubsystem.h"
#include "PacXmas/UI/Menu/PXMenuManager.h"
#include "PacXmas/Utilities/CustomLogs/PXCustomLogs.h"

void APXGameModeMenu::BeginPlay()
{
	Super::BeginPlay();

	const UPXGameInstance* PXGameInstance = Cast<UPXGameInstance>(GetGameInstance());
	PXLevelSubsystem = PXGameInstance->GetSubsystem<UPXLevelSubsystem>();

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
	if (!MenuManager)
	{
		UE_LOG(LogMenuManager, Warning, TEXT("APXGameModeMenu::OpenAppropriateWidget|MenuManager is nullptr"))
		return;
	}
	if (!PXLevelSubsystem)
	{
		UE_LOG(LogSubsystem, Warning, TEXT("APXGameModeMenu::OpenAppropriateWidget|PXLevelSubsystem is nullptr"))
		return;
	}

	const bool bCompletedAllLevels = PXLevelSubsystem->GetCompletedAllLevels();
	const bool bGameStarted = PXLevelSubsystem->GetGameStarted();

	if (!bGameStarted)
	{
		MenuManager->OpenStartGameWidget();
		PXLevelSubsystem->SetGameStarted(true);
	}
	else
	{
		MenuManager->OpenEndGameWidget(bCompletedAllLevels);
	}
}
