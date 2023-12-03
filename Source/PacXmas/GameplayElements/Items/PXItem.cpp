// Copyright (c) 2023 Santa Claus. All rights reserved.


#include "PXItem.h"
#include "PaperSpriteComponent.h"
#include "Components/BoxComponent.h"
#include "PacXmas/DataAssets/Items/PXItemDA.h"
#include "PacXmas/GameplayElements/Characters/Player/PXPlayer.h"
#include "PacXmas/Utilities/CustomLogs/PXCustomLogs.h"

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

void APXItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APXItem::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                             UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep,
                             const FHitResult& SweepResult)
{
	APXPlayer* PlayerCharacter = Cast<APXPlayer>(OtherActor);
	if (PlayerCharacter)
	{
		CollectItem(PlayerCharacter);
	}
}

void APXItem::CollectItem(APXPlayer* PlayerCharacter)
{
	PlayerCharacter->ChangeLook();

	Destroy();
}
