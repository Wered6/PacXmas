// Copyright (c) 2023 Smoking Carrots. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "PacXmas/Utilities/CustomLogs/PXCustomLogs.h"
#include "PXMenuManager.generated.h"

class UPXCelebrationWidget;
class UPXChooseClassWidget;
class UPXEndGameWidget;
class UPXHighscoresWidget;
class UPXChooseNameWidget;
class UPXStartGameWidget;

UCLASS(Blueprintable)
class PACXMAS_API UPXMenuManager : public UObject
{
	GENERATED_BODY()

public:
	void InitializeWidgets();

	void OpenStartGameWidget() const;
	void OpenChooseNameWidget() const;
	void OpenChooseClassWidget() const;
	void OpenHighscoresWidget() const;
	void OpenEndGameWidget() const;
	void OpenCelebrationWidget() const;

private:
	template <typename T>
	T* InitializeWidget(const TSubclassOf<T>& WidgetClass)
	{
		if (!WidgetClass)
		{
			UE_LOG(LogWidget, Warning, TEXT("T* InitializeWidget|WidgetClass is nullptr"))
			return nullptr;
		}

		return CreateWidget<T>(GetWorld(), WidgetClass);
	}

	void OpenWidget(UUserWidget* Widget) const;

	UPROPERTY(EditDefaultsOnly, Category="Menu|StartGame")
	TSubclassOf<UPXStartGameWidget> StartGameWidgetClass;
	UPROPERTY()
	UPXStartGameWidget* StartGameWidget{nullptr};

	UPROPERTY(EditDefaultsOnly, Category="Menu|ChooseName")
	TSubclassOf<UPXChooseNameWidget> ChooseNameWidgetClass;
	UPROPERTY()
	UPXChooseNameWidget* ChooseNameWidget{nullptr};

	UPROPERTY(EditDefaultsOnly, Category="Menu|ChooseClass")
	TSubclassOf<UPXChooseClassWidget> ChooseClassWidgetClass;
	UPROPERTY()
	UPXChooseClassWidget* ChooseClassWidget{nullptr};

	UPROPERTY(EditDefaultsOnly, Category="Menu|Highscores")
	TSubclassOf<UPXHighscoresWidget> HighscoresWidgetClass;
	UPROPERTY()
	UPXHighscoresWidget* HighscoresWidget{nullptr};

	UPROPERTY(EditDefaultsOnly, Category="Menu|EndGame")
	TSubclassOf<UPXEndGameWidget> EndGameWidgetClass;
	UPROPERTY()
	UPXEndGameWidget* EndGameWidget{nullptr};

	UPROPERTY(EditDefaultsOnly, Category="Menu|Celebration")
	TSubclassOf<UPXCelebrationWidget> CelebrationWidgetClass;
	UPROPERTY()
	UPXCelebrationWidget* CelebrationWidget{nullptr};
};
