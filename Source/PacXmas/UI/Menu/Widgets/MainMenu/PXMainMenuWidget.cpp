// Copyright (c) 2023 Smoking Carrots. All rights reserved.


#include "PXMainMenuWidget.h"
#include "PacXmas/UI/Menu/PXMenuManager.h"
#include "PacXmas/Utilities/CustomLogs/PXCustomLogs.h"

void UPXMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	InitializeMenuManager();

	if (!PXMenuManager)
	{
		UE_LOG(LogMenuManager, Warning, TEXT("UPXMainMenuWidget::NativeConstruct|PXMenuManager is nullptr"))
		return;
	}

	PXMenuManager->InitializeWidgets();
}

void UPXMainMenuWidget::OpenChooseNameWidget() const
{
	if (!PXMenuManager)
	{
		UE_LOG(LogMenuManager, Warning, TEXT("UPXMainMenuWidget::OpenChooseNameWidget|PXMenuManager is nullptr"))
		return;
	}

	PXMenuManager->OpenChooseNameWidget();
}

void UPXMainMenuWidget::OpenHighscoresWidget() const
{
	if (!PXMenuManager)
	{
		UE_LOG(LogMenuManager, Warning, TEXT("UPXMainMenuWidget::OpenHighscoresWidget|PXMenuManager is nullptr"))
		return;
	}

	PXMenuManager->OpenHighscoresWidget();
}

void UPXMainMenuWidget::InitializeMenuManager()
{
	if (!PXMenuManagerClass)
	{
		UE_LOG(LogClass, Warning, TEXT("UPXMainMenuWidget::InitializeMenuManager|PXMenuManagerClass is nullptr"))
		return;
	}

	PXMenuManager = NewObject<UPXMenuManager>(this, PXMenuManagerClass);
}
