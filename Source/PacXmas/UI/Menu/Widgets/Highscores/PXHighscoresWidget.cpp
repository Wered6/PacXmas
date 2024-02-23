// Copyright (c) 2023 Smoking Carrots. All rights reserved.


#include "PXHighscoresWidget.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "PacXmas/Subsystems/ScoreSubsystem/PXScoreSubsystem.h"
#include "PacXmas/Utilities/CustomLogs/PXCustomLogs.h"

void UPXHighscoresWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
	
	InitializeScoreSubsystem();
}

void UPXHighscoresWidget::InitializeScoreSubsystem()
{
	const UGameInstance* GameInstance = GetGameInstance();

	if (!GameInstance)
	{
		UE_LOG(LogGameInstance, Warning, TEXT("UPXHighscoresWidget::InitializeScoreSubsystem|GameInstance is nullptr"))
		return;
	}

	PXScoreSubsystem = GameInstance->GetSubsystem<UPXScoreSubsystem>();
}

void UPXHighscoresWidget::UpdateHighscoresWidget() const
{
	if (!PXScoreSubsystem)
	{
		UE_LOG(LogSubsystem, Warning, TEXT("UPXHighscoresWidget::UpdateHighscoresWidget|PXScoreSubsystem is nullptr"))
		return;
	}
	if (!Nicknames)
	{
		UE_LOG(LogWidget, Warning, TEXT("UPXHighscoresWidget::UpdateHighscoresWidget|Nicknames is nullptr"))
		return;
	}
	if (!Highscores)
	{
		UE_LOG(LogWidget, Warning, TEXT("UPXHighscoresWidget::UpdateHighscoresWidget|Highscores is nullptr"))
		return;
	}

	TArray<FHighScoreEntry> HighscoresArr = PXScoreSubsystem->GetHighscores();

	for (int i = 0; i < HighscoresArr.Num(); i++)
	{
		const FText NicknameText = FText::FromString(HighscoresArr[i].PlayerName);
		const FText HighScoreText = FText::AsNumber(HighscoresArr[i].Score);

		Cast<UTextBlock>(Nicknames->GetChildAt(i))->SetText(NicknameText);
		Cast<UTextBlock>(Highscores->GetChildAt(i))->SetText(HighScoreText);
	}
}
