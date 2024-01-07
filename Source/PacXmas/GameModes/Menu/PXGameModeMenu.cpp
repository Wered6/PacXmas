// Copyright (c) 2023 Smoking Carrots. All rights reserved.


#include "PXGameModeMenu.h"
#include "PacXmas/GameInstance/PXGameInstance.h"
#include "PacXmas/Subsystems/LevelSubsystem/PXLevelSubsystem.h"
#include "PacXmas/Subsystems/ScoreSubsystem/PXScoreSubsystem.h"
#include "PacXmas/UI/Menu/PXMenuManager.h"
#include "PacXmas/Utilities/CustomLogs/PXCustomLogs.h"

void APXGameModeMenu::BeginPlay()
{
	Super::BeginPlay();

	const UPXGameInstance* PXGameInstance = Cast<UPXGameInstance>(GetGameInstance());
	PXLevelSubsystem = PXGameInstance->GetSubsystem<UPXLevelSubsystem>();
	PXScoreSubsystem = PXGameInstance->GetSubsystem<UPXScoreSubsystem>();

	if (!PXScoreSubsystem)
	{
		UE_LOG(LogSubsystem, Warning, TEXT("APXGameModeMenu::BeginPlay|PXScoreSubsystem is nullptr"))
		return;
	}

	PXScoreSubsystem->UpdateHighScores();
	PXScoreSubsystem->ResetScore();

	if (!PXMenuManagerClass)
	{
		UE_LOG(LogMenuManager, Warning, TEXT("APXGameModeMenu::BeginPlay|MenuManagerClass is nullptr"))
		return;
	}

	PXMenuManager = NewObject<UPXMenuManager>(this, PXMenuManagerClass);

	if (!PXMenuManager)
	{
		UE_LOG(LogMenuManager, Warning, TEXT("APXGameModeMenu::BeginPlay|MenuManager is nullptr"))
		return;
	}

	PXMenuManager->InitializeWidgets();
	OpenAppropriateWidget();
}

void APXGameModeMenu::OpenAppropriateWidget() const
{
	if (!PXMenuManager)
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
		PXMenuManager->OpenStartGameWidget();
		PXLevelSubsystem->SetGameStarted(true);
	}
	else
	{
		PXMenuManager->OpenEndGameWidget(bCompletedAllLevels);
	}
}
