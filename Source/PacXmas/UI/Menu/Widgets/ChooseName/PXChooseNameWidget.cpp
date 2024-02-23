// Copyright (c) 2023 Smoking Carrots. All rights reserved.


#include "PXChooseNameWidget.h"
#include "Components/EditableText.h"
#include "PacXmas/Subsystems/ScoreSubsystem/PXScoreSubsystem.h"
#include "PacXmas/Utilities/CustomLogs/PXCustomLogs.h"

void UPXChooseNameWidget::NativeConstruct()
{
	Super::NativeConstruct();

	InitializeScoreSubsystem();
}

void UPXChooseNameWidget::InitializeScoreSubsystem()
{
	const UGameInstance* GameInstance = GetGameInstance();

	if (!GameInstance)
	{
		UE_LOG(LogGameInstance, Warning, TEXT("UPXChooseNameWidget::InitializeScoreSubsystem|GameInstance is nullptr"))
		return;
	}

	PXScoreSubsystem = GameInstance->GetSubsystem<UPXScoreSubsystem>();
}

bool UPXChooseNameWidget::SetPlayerName(const bool bIsCommitted) const
{
	if (!Nickname)
	{
		UE_LOG(LogWidget, Warning, TEXT("UPXChooseNameWidget::SetPlayerNameWithEnter|Nickname is nullptr"))
		return false;
	}
	if (!PXScoreSubsystem)
	{
		UE_LOG(LogSubsystem, Warning, TEXT("UPXChooseNameWidget::SetPlayerNameWithEnter|PXScoreSubsystem is nullptr"))
		return false;
	}

	// Only proceed if the action is a committed one
	if (!bIsCommitted)
	{
		return false;
	}

	// Get the new player name from the Nickname widget
	const FString NewPlayerName = Nickname->GetText().ToString();

	// If the nickname doesn't meet the minimum length, set focus on the Nickname widget and return false
	if (!IsNicknameMinLen())
	{
		Nickname->SetKeyboardFocus();
		return false;
	}

	// If no early return, set the player name in the score subsystem and return true
	PXScoreSubsystem->SetPlayerName(NewPlayerName);
	return true;
}

bool UPXChooseNameWidget::IsNicknameMinLen() const
{
	return Nickname->GetText().ToString().Len() >= MinNicknameLen;
}
