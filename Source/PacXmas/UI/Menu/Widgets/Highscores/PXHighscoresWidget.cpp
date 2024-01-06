// Copyright (c) 2023 Smoking Carrots. All rights reserved.


#include "PXHighscoresWidget.h"
#include "PacXmas/UI/Menu/PXMenuManager.h"

void UPXHighscoresWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (!MenuManagerClass)
	{
		UE_LOG(LogMenuManager, Warning, TEXT("UPXHighscoresWidget::NativeConstruct|MenuManagerClass is nullptr"))
		return;
	}

	MenuManager = NewObject<UPXMenuManager>(this, MenuManagerClass);

	if (!MenuManager)
	{
		UE_LOG(LogMenuManager, Warning, TEXT("UPXHighscoresWidget::NativeConstruct|MenuManager is nullptr"))
		return;
	}

	MenuManager->InitializeWidgets();
}

void UPXHighscoresWidget::OpenStartGameWidget() const
{
	if (!MenuManager)
	{
		UE_LOG(LogMenuManager, Warning, TEXT("UPXHighscoresWidget::OpenStartGameWidget(|MenuManager is nullptr"))
		return;
	}

	MenuManager->OpenStartGameWidget();
}
