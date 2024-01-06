// Copyright (c) 2023 Smoking Carrots. All rights reserved.


#include "PacXmas/GameplayElements/Interactables/Board/PXBoard.h"
#include "PaperSpriteComponent.h"
#include "Components/BoxComponent.h"
#include "PacXmas/DataAssets/Interactables/Board/PXBoardDA.h"
#include "PacXmas/GameInstance/PXGameInstance.h"
#include "PacXmas/Subsystems/LevelSubsystem/PXLevelSubsystem.h"
#include "PacXmas/Subsystems/ScoreSubsystem/PXScoreSubsystem.h"
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

	const UGameInstance* GameInstance = GetGameInstance();

	if (!GameInstance)
	{
		UE_LOG(LogGameInstance, Warning, TEXT("APXBoard::BeginPlay|GameInstance is nullptr"))
		return;
	}

	PXScoreSubsystem = GameInstance->GetSubsystem<UPXScoreSubsystem>();
}

void APXBoard::FillBoard()
{
	MusicSheetCount++;

	PXScoreSubsystem->AddScore(5);

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

	if (MusicSheetCount >= 4)
	{
		CompleteLevel();
		PXScoreSubsystem->AddScore(10);
	}
}

void APXBoard::CompleteLevel() const
{
	const UPXGameInstance* PXGameInstance = Cast<UPXGameInstance>(GetGameInstance());

	if (!PXGameInstance)
	{
		UE_LOG(LogGameInstance, Warning, TEXT("APXBoard::CompleteLevel|PXGameInstance is nullptr"))
		return;
	}

	UPXLevelSubsystem* PXLevelSubsystem = PXGameInstance->GetSubsystem<UPXLevelSubsystem>();

	if (!PXLevelSubsystem)
	{
		UE_LOG(LogSubsystem, Warning, TEXT("APXBoard::CompleteLevel|PXLevelSubsystem is nullptr"))
		return;
	}

	PXLevelSubsystem->CompleteLevel();
}
