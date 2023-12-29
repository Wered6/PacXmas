// Copyright (c) 2023 Santa Claus. All rights reserved.


#include "PXItem.h"
#include "PaperSpriteComponent.h"
#include "Components/BoxComponent.h"
#include "PacXmas/DataAssets/Items/PXItemDA.h"
#include "PacXmas/GameplayElements/Characters/Player/PXPlayer.h"
#include "PacXmas/Utilities/CustomLogs/PXCustomLogs.h"

APXItem::APXItem()
{
	CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Box"));
	RootComponent = CollisionComponent;
	CollisionComponent->SetCollisionProfileName(TEXT("Item"));

	PaperSpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Paper Sprite"));
	PaperSpriteComponent->SetupAttachment(CollisionComponent);
	PaperSpriteComponent->SetCollisionProfileName(TEXT("NoCollision"));

	const FVector BoxExtent = FVector(CollisionSize / 2);
	CollisionComponent->SetBoxExtent(BoxExtent);
	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &APXItem::OnOverlapBegin);
}

void APXItem::BeginPlay()
{
	Super::BeginPlay();

	if (!PaperSpriteComponent)
	{
		UE_LOG(LogItem, Warning, TEXT("APXItem::BeginPlay|PaperSpriteComponent is nullptr"))
		return;
	}
	if (!ItemDA)
	{
		UE_LOG(LogItem, Warning, TEXT("APXItem::BeginPlay|ItemDA is nullptr"))
		return;
	}

	PaperSpriteComponent->SetSprite(ItemDA->Sprite);
}

void APXItem::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                             UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep,
                             const FHitResult& SweepResult)
{
	APXPlayer* PXPlayer = Cast<APXPlayer>(OtherActor);

	if (!PXPlayer)
	{
		UE_LOG(LogActor, Warning, TEXT("APXItem::OnOverlapBegin|PXPlayer is nullptr"))
		return;
	}

	CollectItem(PXPlayer);
}

void APXItem::CollectItem(APXPlayer* PlayerCharacter)
{
	Destroy();
}
