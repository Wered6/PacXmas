// Copyright (c) 2023 Smoking Carrots. All rights reserved.


#include "PXBaseMenuWidget.h"
#include "PacXmas/UI/Menu/MenuManager/PXMenuManager.h"

void UPXBaseMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	InitializeMenuManager();
}

void UPXBaseMenuWidget::InitializeMenuManager()
{
	if (!PXMenuManagerClass)
	{
		UE_LOG(LogClass, Warning, TEXT("UPXBaseMenuWidget::InitializeMenuManager|PXMenuManagerClass is nullptr"))
		return;
	}

	PXMenuManager = NewObject<UPXMenuManager>(this, PXMenuManagerClass);
}
