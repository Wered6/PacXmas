// Copyright (c) 2023 Santa Claus. All rights reserved.


#include "PXChooseClassWidget.h"
#include "PacXmas/GameInstance/PXGameInstance.h"
#include "PacXmas/Utilities/CustomLogs/PXCustomLogs.h"

void UPXChooseClassWidget::NativeConstruct()
{
	Super::NativeConstruct();

	PXGameInstance = Cast<UPXGameInstance>(GetGameInstance());
}

void UPXChooseClassWidget::PickGirl() const
{
	if (!PXGameInstance)
	{
		UE_LOG(LogGameInstance, Warning, TEXT("UPXChooseClassWidget::PickGirl|GameInstance is nullptr"))
		return;
	}

	PXGameInstance->SetPlayerClass(EPlayerClass::Girl);
}

void UPXChooseClassWidget::PickBoy() const
{
	if (!PXGameInstance)
	{
		UE_LOG(LogGameInstance, Warning, TEXT("UPXChooseClassWidget::PickBoy|GameInstance is nullptr"))
	}

	PXGameInstance->SetPlayerClass(EPlayerClass::Boy);
}
