// Copyright (c) 2023 Smoking Carrots. All rights reserved.


#include "PacXmas/GameplayElements/Interactables/Board/PXBoard.h"
#include "PaperSpriteComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PacXmas/DataAssets/Interactables/Board/PXBoardDA.h"
#include "PacXmas/GameInstance/PXGameInstance.h"
#include "PacXmas/Subsystems/LevelSubsystem/PXLevelSubsystem.h"
#include "PacXmas/Subsystems/ScoreSubsystem/PXScoreSubsystem.h"
#include "PacXmas/UI/HUD/PXHUD.h"
#include "PacXmas/Utilities/CustomLogs/PXCustomLogs.h"

APXBoard::APXBoard()
{
	CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Box"));
	RootComponent = CollisionComponent;
	CollisionComponent->SetCollisionProfileName(TEXT("Board"));

	PaperSpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Paper Sprite Component"));
	PaperSpriteComponent->SetupAttachment(RootComponent);
	PaperSpriteComponent->SetCollisionProfileName(TEXT("NoCollision"));

	const FVector BoxExtent = FVector(CollisionSize / 2);
	CollisionComponent->SetBoxExtent(BoxExtent);
}

void APXBoard::BeginPlay()
{
	Super::BeginPlay();

	if (!PaperSpriteComponent)
	{
		UE_LOG(LogItem, Warning, TEXT("APXBoard::BeginPlay|PaperSpriteComponent is nullptr"))
		return;
	}
	if (!BoardDA)
	{
		UE_LOG(LogItem, Warning, TEXT("APXBoard::BeginPlay|BoardDA is nullptr"))
		return;
	}

	PaperSpriteComponent->SetSprite(BoardDA->Sprite0);

	InitializeScoreSubsystem();
	InitializeLeveSubsystem();
}

void APXBoard::FillBoard()
{
	MusicSheetCount++;

	PlayBringMusicSheetSound();

	if (MusicSheetCount >= 4)
	{
		CompleteLevel();
		AddAndPopupScore(EScoreTypes::BringAllMusicSheets);

		return;
	}

	AddAndPopupScore(EScoreTypes::BringMusicSheet);

	switch (MusicSheetCount)
	{
	case 1:
		PaperSpriteComponent->SetSprite(BoardDA->Sprite1);
		break;
	case 2:
		PaperSpriteComponent->SetSprite(BoardDA->Sprite2);
		break;
	case 3:
		PaperSpriteComponent->SetSprite(BoardDA->Sprite3);
		break;
	case 4:
		PaperSpriteComponent->SetSprite(BoardDA->Sprite4);
		break;
	default:
		PaperSpriteComponent->SetSprite(BoardDA->Sprite0);
		break;
	}
}

void APXBoard::InitializeLeveSubsystem()
{
	const UPXGameInstance* PXGameInstance = Cast<UPXGameInstance>(GetGameInstance());

	if (!PXGameInstance)
	{
		UE_LOG(LogGameInstance, Warning, TEXT("APXBoard::InitializeLeveSubsystem|PXGameInstance is nullptr"))
		return;
	}

	PXLevelSubsystem = PXGameInstance->GetSubsystem<UPXLevelSubsystem>();
}

void APXBoard::InitializeScoreSubsystem()
{
	const UPXGameInstance* PXGameInstance = Cast<UPXGameInstance>(GetGameInstance());

	if (!PXGameInstance)
	{
		UE_LOG(LogGameInstance, Warning, TEXT("APXBoard::InitializeScoreSubsystem|PXGameInstance is nullptr"))
		return;
	}

	PXScoreSubsystem = PXGameInstance->GetSubsystem<UPXScoreSubsystem>();
}

void APXBoard::PlayBringMusicSheetSound() const
{
	if (!BringMusicSheetSound)
	{
		UE_LOG(LogSound, Warning, TEXT("APXBoard::PlayBringMusicSheetSound|BringMusicSheetSound is nullptr"))
		return;
	}

	UGameplayStatics::PlaySoundAtLocation(this, BringMusicSheetSound, GetActorLocation());
}

void APXBoard::AddAndPopupScore(const EScoreTypes ScoreType) const
{
	if (!PXScoreSubsystem)
	{
		UE_LOG(LogSubsystem, Warning, TEXT("APXBoard::AddAndPopupScore|PXScoreSubsystem is nullptr"))
		return;
	}

	const APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

	if (!PlayerController)
	{
		UE_LOG(LogController, Warning, TEXT("APXBoard::AddAndPopupScore|PlayerController is nullptr"))
		return;
	}

	APXHUD* PXHUD = Cast<APXHUD>(PlayerController->GetHUD());

	if (!PXHUD)
	{
		UE_LOG(LogHUD, Warning, TEXT("APXBoard::AddAndPopupScore|PXHUD is nullptr"))
		return;
	}

	PXScoreSubsystem->AddScore(ScoreType);
	PXHUD->DisplayScorePopup(ScoreType);
	PXHUD->UpdateScore();
}

void APXBoard::CompleteLevel() const
{
	if (!PXLevelSubsystem)
	{
		UE_LOG(LogSubsystem, Warning, TEXT("APXBoard::CompleteLevel|PXLevelSubsystem is nullptr"))
		return;
	}

	PXLevelSubsystem->OpenRandomLevel();

	// todo set some timer and freeze
}
