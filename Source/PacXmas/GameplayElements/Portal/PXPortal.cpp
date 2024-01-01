// Copyright (c) 2023 Santa Claus. All rights reserved.


#include "PXPortal.h"
#include "Components/BoxComponent.h"
#include "PacXmas/GameplayElements/Characters/Player/PXPlayer.h"
#include "PacXmas/Utilities/CustomLogs/PXCustomLogs.h"

APXPortal::APXPortal()
{
	CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Box"));

	if (!CollisionComponent)
	{
		UE_LOG(LogComponent, Warning, TEXT("APXPortal::APXPortal|CollisionComponent is nullptr"))
		return;
	}

	RootComponent = CollisionComponent;
	CollisionComponent->SetCollisionProfileName(TEXT("Portal"));

	const FVector BoxExtent = FVector(CollisionSize / 2);
	CollisionComponent->SetBoxExtent(BoxExtent);
	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &APXPortal::OnOverlapBegin);
}

void APXPortal::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                               UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep,
                               const FHitResult& SweepResult)
{
	APXPlayer* PXPlayer = Cast<APXPlayer>(OtherActor);

	if (!PXPlayer)
	{
		UE_LOG(LogActor, Warning, TEXT("APXPortal::OnOverlapBegin|PXPlayer is nullptr"))
		return;
	}

	PXPlayer->TeleportTo(TargetDestination, PXPlayer->GetActorRotation());
	PXPlayer->ResetMovementComponent();
}
