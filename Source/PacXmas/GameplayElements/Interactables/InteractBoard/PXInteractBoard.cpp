// Copyright (c) 2023 Santa Claus. All rights reserved.


#include "PXInteractBoard.h"
#include "EngineUtils.h"
#include "Components/BoxComponent.h"
#include "PacXmas/GameplayElements/Characters/Player/PXPlayer.h"
#include "PacXmas/GameplayElements/Interactables/Board/PXBoard.h"

APXInteractBoard::APXInteractBoard()
{
	PrimaryActorTick.bCanEverTick = false;

	CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider Box"));
	RootComponent = CollisionComponent;
	CollisionComponent->SetBoxExtent(FVector(CollisionWidth / 2, CollisionHeight / 2, CollisionDepth / 2));
	CollisionComponent->SetCollisionProfileName(TEXT("InteractBoard"));

	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &APXInteractBoard::OnOverlapBegin);
}

void APXInteractBoard::BeginPlay()
{
	Super::BeginPlay();
}

void APXInteractBoard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APXInteractBoard::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                      UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep,
                                      const FHitResult& SweepResult)
{
	APXPlayer* PlayerCharacter = Cast<APXPlayer>(OtherActor);
	const APXBoard* PXBoard = SearchBoard();

	if (!PlayerCharacter)
	{
		UE_LOG(LogActor, Warning, TEXT("APXInteractBoard::OnOverlapBegin|PlayerCharacter is nullptr"))
		return;
	}
	if (!PXBoard)
	{
		UE_LOG(LogActor, Warning, TEXT("APXInteractBoard::OnOverlapBegin|PXBoard is nullptr"))
		return;
	}

	const bool bHasMusicSheet = PlayerCharacter->GetHasMusicSheet();
	const uint8_t MusicSheetCount = PlayerCharacter->GetMusicSheetCount();

	if (bHasMusicSheet)
	{
		PXBoard->FillBoard(MusicSheetCount);
		PlayerCharacter->DropMusicSheet();
	}
}

APXBoard* APXInteractBoard::SearchBoard() const
{
	for (TActorIterator<APXBoard> It(GetWorld()); It; ++It)
	{
		APXBoard* PXBoard = *It;
		if (IsValid(PXBoard))
		{
			return PXBoard;
		}
	}

	return nullptr;
}
