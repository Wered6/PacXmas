// Copyright (c) 2023 Santa Claus. All rights reserved.


#include "PacXmas/GameplayElements/Interactables/Board/PXBoard.h"
#include "PaperSpriteComponent.h"
#include "Components/BoxComponent.h"
#include "PacXmas/DataAssets/Interactables/Board/PXBoardDA.h"
#include "PacXmas/Utilities/CustomLogs/PXCustomLogs.h"

APXBoard::APXBoard()
{
	PrimaryActorTick.bCanEverTick = false;

	CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Box"));
	RootComponent = CollisionComponent;
	CollisionComponent->SetCollisionProfileName(TEXT("Board"));

	PaperSpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Paper Sprite Component"));
	PaperSpriteComponent->SetupAttachment(RootComponent);
	PaperSpriteComponent->SetCollisionProfileName(TEXT("NoCollision"));

	const FVector BoxExtent = FVector(CollisionWidth / 2, CollisionDepth / 2, CollisionHeight / 2);
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

	PaperSpriteComponent->SetSprite(BoardDA->Sprite1);
}

void APXBoard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
