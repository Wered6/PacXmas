// Copyright (c) 2023 Smoking Carrots. All rights reserved.


#include "PXChooseClassWidget.h"
#include "PacXmas/GameInstance/PXGameInstance.h"
#include "PacXmas/Subsystems/ClassSubsystem/PXClassSubsystem.h"
#include "PacXmas/Utilities/CustomLogs/PXCustomLogs.h"

void UPXChooseClassWidget::NativeConstruct()
{
	Super::NativeConstruct();

	InitializeClassSubsystem();
}

void UPXChooseClassWidget::PickGirl() const
{
	if (!PXClassSubsystem)
	{
		UE_LOG(LogGameInstance, Warning, TEXT("UPXChooseClassWidget::PickGirl|PXClassSubsystem is nullptr"))
		return;
	}

	PXClassSubsystem->SetPlayerClass(EPlayerClass::Girl);
}

void UPXChooseClassWidget::PickBoy() const
{
	if (!PXClassSubsystem)
	{
		UE_LOG(LogGameInstance, Warning, TEXT("UPXChooseClassWidget::PickBoy|PXClassSubsystem is nullptr"))
	}

	PXClassSubsystem->SetPlayerClass(EPlayerClass::Boy);
}

void UPXChooseClassWidget::InitializeClassSubsystem()
{
	const UPXGameInstance* PXGameInstance = Cast<UPXGameInstance>(GetGameInstance());

	if (!PXGameInstance)
	{
		UE_LOG(LogGameInstance, Warning,
		       TEXT("UPXChooseClassWidget::InitializeClassSubsystem|PXGameInstance is nullptr"))
		return;
	}

	PXClassSubsystem = PXGameInstance->GetSubsystem<UPXClassSubsystem>();
}
