// Copyright (c) 2023 Smoking Carrots. All rights reserved.


#include "PXScorePopup.h"
#include "Animation/WidgetAnimation.h"
#include "Components/HorizontalBox.h"
#include "Components/Image.h"
#include "Kismet/GameplayStatics.h"
#include "PacXmas/UI/HUD/DigitTextureManager/PXDigitTextureManager.h"
#include "PacXmas/Utilities/CustomLogs/PXCustomLogs.h"

void UPXScorePopup::Play(const int32 Score, const APlayerController* PlayerController)
{
	InitializeDigitTextureManager();

	SetScoreInHorizontalBox(Score);
	SetPositionInViewport(PlayerController);
	AddToViewport();
	PlayFadingUpAnimation();
	SetTimerRemoveFromParent();
}

void UPXScorePopup::InitializeDigitTextureManager()
{
	if (!PXDigitTextureManagerClass)
	{
		UE_LOG(LogClass, Warning,
		       TEXT("UPXScorePopup::InitializeDigitTextureManager|PXDigitTextureManagerClass is nullptr"))
		return;
	}

	PXDigitTextureManager = NewObject<UPXDigitTextureManager>(this, PXDigitTextureManagerClass);
}

void UPXScorePopup::SetScoreInHorizontalBox(const int32 Score) const
{
	if (!PXDigitTextureManager)
	{
		UE_LOG(LogManager, Warning, TEXT("UPXScorePopup::SetScoreInHorizontalBox|PXDigitTextureManager is nullptr"))
		return;
	}
	if (!ScoreHorizontalBox)
	{
		UE_LOG(LogWidget, Warning, TEXT("UPXScorePopup::SetScoreInHorizontalBox|ScoreHorizontalBox is nullptr"))
		return;
	}

	PXDigitTextureManager->SetScoreInHorizontalBox(ScoreHorizontalBox, Score, CharSize, true);
}

void UPXScorePopup::SetPositionInViewport(const APlayerController* PlayerController)
{
	if (!PlayerController)
	{
		UE_LOG(LogController, Warning, TEXT("UPXScorePopup::SetPositionInViewport|PlayerController is nullptr"))
		return;
	}

	const APawn* Pawn = PlayerController->GetPawn();

	if (!Pawn)
	{
		UE_LOG(LogActor, Warning, TEXT("UPXScorePopup::SetPositionInViewport|Pawn is nullptr"))
		return;
	}

	const FVector PawnLocation = Pawn->GetActorLocation();
	FVector2D ScreenPosition;
	UGameplayStatics::ProjectWorldToScreen(PlayerController, PawnLocation, ScreenPosition);

	Super::SetPositionInViewport(ScreenPosition);
}

void UPXScorePopup::PlayFadingUpAnimation()
{
	if (!FadingUp)
	{
		UE_LOG(LogAnimation, Warning, TEXT("UPXScorePopup::PlayAnimation|FadingUp is nullptr"))
		return;
	}

	PlayAnimation(FadingUp);
}

void UPXScorePopup::SetTimerRemoveFromParent()
{
	// Set a timer to remove the widget after animation has finished
	const float AnimationDuration = FadingUp->GetEndTime() - FadingUp->GetStartTime();

	FTimerHandle TimerHandle;
	const FTimerDelegate TimerDelegate = FTimerDelegate::CreateUObject(this, &UPXScorePopup::RemoveFromParent);
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, AnimationDuration, false);
}
