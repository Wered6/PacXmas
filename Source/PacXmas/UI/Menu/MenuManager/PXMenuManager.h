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
	void OpenChooseNameWidget();
	void OpenChooseClassWidget();
	void OpenHighscoresWidget();
	void OpenEndGameWidget();
	void OpenCelebrationWidget();
	void OpenSettingsWidget();
	void OpenAudioSettingsWidget();

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

	UPROPERTY(EditDefaultsOnly, Category="Menu|ChooseName")
	TSubclassOf<UPXChooseNameWidget> PXChooseNameWidgetClass;
	UPROPERTY()
	UPXChooseNameWidget* PXChooseNameWidget{nullptr};

	UPROPERTY(EditDefaultsOnly, Category="Menu|ChooseClass")
	TSubclassOf<UPXChooseClassWidget> PXChooseClassWidgetClass;
	UPROPERTY()
	UPXChooseClassWidget* PXChooseClassWidget{nullptr};

	UPROPERTY(EditDefaultsOnly, Category="Menu|Highscores")
	TSubclassOf<UPXHighscoresWidget> PXHighscoresWidgetClass;
	UPROPERTY()
	UPXHighscoresWidget* PXHighscoresWidget{nullptr};

	UPROPERTY(EditDefaultsOnly, Category="Menu|EndGame")
	TSubclassOf<UPXEndGameWidget> PXEndGameWidgetClass;
	UPROPERTY()
	UPXEndGameWidget* PXEndGameWidget{nullptr};

	UPROPERTY(EditDefaultsOnly, Category="Menu|Celebration")
	TSubclassOf<UPXCelebrationWidget> PXCelebrationWidgetClass;
	UPROPERTY()
	UPXCelebrationWidget* PXCelebrationWidget{nullptr};

	UPROPERTY(EditDefaultsOnly, Category="Menu|Settings")
	TSubclassOf<UPXSettingsWidget> PXSettingsWidgetClass;
	UPROPERTY()
	UPXSettingsWidget* PXSettingsWidget{nullptr};

	UPROPERTY(EditDefaultsOnly, Category="Menu|Settings|Audio")
	TSubclassOf<UPXAudioSettingsWidget> PXAudioSettingsWidgetClass;
	UPROPERTY()
	UPXAudioSettingsWidget* PXAudioSettingsWidget{nullptr};
};
