// Copyright (c) 2023 Smoking Carrots. All rights reserved.


#include "PXPortal.h"
#include "Components/BoxComponent.h"
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
	if (!OtherActor)
	{
		UE_LOG(LogActor, Warning, TEXT("APXPortal::OnOverlapBegin|OtherActor is nullptr"))
		return;
	}

	OtherActor->TeleportTo(TargetDestination, OtherActor->GetActorRotation());
	// todo add sound when teleporting something
	// todo consider delegate to reset targetlocation
}
