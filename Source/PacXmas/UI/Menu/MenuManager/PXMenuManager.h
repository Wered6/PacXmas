// Copyright (c) 2023 Smoking Carrots. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "PXMenuManager.generated.h"

class UPXAudioSettingsWidget;
class UPXSettingsWidget;
class UPXCelebrationWidget;
class UPXChooseClassWidget;
class UPXEndGameWidget;
class UPXHighscoresWidget;
class UPXChooseNameWidget;
class UPXMainMenuWidget;

UCLASS(Blueprintable)
class PACXMAS_API UPXMenuManager : public UObject
{
	GENERATED_BODY()

public:
	void OpenMainMenuWidget();

private:
	template <typename T>
	T* InitializeWidget(const TSubclassOf<T>& WidgetClass)
	{
		if (!WidgetClass)
		{
			UE_LOG(LogClass, Warning, TEXT("T* InitializeWidget|WidgetClass is nullptr"))
			return nullptr;
		}

		return CreateWidget<T>(GetWorld(), WidgetClass);
	}

	void OpenWidget(UUserWidget* Widget) const;

	UPROPERTY(EditDefaultsOnly, Category="Menu|StartGame")
	TSubclassOf<UPXMainMenuWidget> PXMainMenuWidgetClass;
	UPROPERTY()
	UPXMainMenuWidget* PXMainMenuWidget{nullptr};
};
