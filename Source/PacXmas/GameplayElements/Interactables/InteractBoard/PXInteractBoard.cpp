// Copyright (c) 2023 Santa Claus. All rights reserved.


#include "PXInteractBoard.h"
#include "EngineUtils.h"
#include "Components/BoxComponent.h"
#include "PacXmas/GameModes/Gameplay/PXGameModeGameplay.h"
#include "PacXmas/GameplayElements/Characters/Player/PXPlayer.h"
#include "PacXmas/GameplayElements/Interactables/Board/PXBoard.h"

APXInteractBoard::APXInteractBoard()
{
	CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider Box"));
	RootComponent = CollisionComponent;
	CollisionComponent->SetCollisionProfileName(TEXT("InteractBoard"));

	const FVector BoxExtent = FVector(CollisionSize / 2);
	CollisionComponent->SetBoxExtent(BoxExtent);
	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &APXInteractBoard::OnOverlapBegin);
}

void APXInteractBoard::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                      UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep,
                                      const FHitResult& SweepResult)
{
	APXPlayer* PXPlayer = Cast<APXPlayer>(OtherActor);
	APXBoard* PXBoard = FindBoard();
	const APXGameModeGameplay* PXGameModeGameplay = GetWorld()->GetAuthGameMode<APXGameModeGameplay>();

	if (!PXPlayer)
	{
		UE_LOG(LogActor, Warning, TEXT("APXInteractBoard::OnOverlapBegin|PlayerCharacter is nullptr"))
		return;
	}
	if (!PXBoard)
	{
		UE_LOG(LogActor, Warning, TEXT("APXInteractBoard::OnOverlapBegin|PXBoard is nullptr"))
		return;
	}
	if (!PXGameModeGameplay)
	{
		UE_LOG(LogGameMode, Warning, TEXT("APXInteractBoard::OnOverlapBegin|PXGameModeGameplay is nullptr"))
		return;
	}

	const bool bHasMusicSheet = PXPlayer->GetHasMusicSheet();

	if (bHasMusicSheet)
	{
		PXBoard->FillBoard();
		PXPlayer->DropMusicSheet();
		PXGameModeGameplay->SpawnMusicSheet();
	}
}

APXBoard* APXInteractBoard::FindBoard() const
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
