// Copyright (c) 2023 Smoking Carrots. All rights reserved.


#include "PXCelebrationWidget.h"
#include "Components/TextBlock.h"
#include "PacXmas/Subsystems/ScoreSubsystem/PXScoreSubsystem.h"
#include "PacXmas/Utilities/CustomLogs/PXCustomLogs.h"

void UPXCelebrationWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	InitializeScoreSubsystem();
}

void UPXCelebrationWidget::InitializeScoreSubsystem()
{
	const UGameInstance* GameInstance = GetGameInstance();

	if (!GameInstance)
	{
		UE_LOG(LogGameInstance, Warning, TEXT("UPXCelebrationWidget::InitializeScoreSubsystem|GameInstance is nullptr"))
		return;
	}

	PXScoreSubsystem = GameInstance->GetSubsystem<UPXScoreSubsystem>();
}

void UPXCelebrationWidget::SetScoreText() const
{
	if (!PXScoreSubsystem)
	{
		UE_LOG(LogSubsystem, Warning, TEXT("UPXCelebrationWidget::SetScoreText|PXScoreSubsystem is nullpt"))
		return;
	}

	const int32 ScorePoints = PXScoreSubsystem->GetScore();
	const FText ScoreText = FText::AsNumber(ScorePoints);

	Score->SetText(ScoreText);
}
