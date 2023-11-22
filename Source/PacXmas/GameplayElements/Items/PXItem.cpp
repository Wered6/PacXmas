// Copyright (c) 2023 Santa Claus. All rights reserved.


#include "PXItem.h"
#include "PaperSpriteComponent.h"
#include "Components/BoxComponent.h"
#include "PacXmas/DataAssets/Items/PXItemDA.h"

APXItem::APXItem()
{
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Box"));
	RootComponent = CollisionComponent;
	CollisionComponent->SetCollisionProfileName(TEXT("Item"));

	PaperSpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Paper Sprite"));
	PaperSpriteComponent->SetupAttachment(RootComponent);
	PaperSpriteComponent->SetCollisionProfileName(TEXT("NoCollision"));

	const FVector BoxExtent = FVector(CollisionWidth / 2, CollisionDepth / 2, CollisionHeight / 2);
	CollisionComponent->SetBoxExtent(BoxExtent);
}

void APXItem::BeginPlay()
{
	Super::BeginPlay();

	PaperSpriteComponent->SetSprite(ItemDA->SpriteComp);
}

void APXItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
