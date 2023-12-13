// Copyright (c) 2023 Santa Claus. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PXInteractBoard.generated.h"

class APXBoard;
class UBoxComponent;

UCLASS()
class PACXMAS_API APXInteractBoard : public AActor
{
	GENERATED_BODY()

public:
	APXInteractBoard();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

protected:
	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                            UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep,
	                            const FHitResult& SweepResult);

private:
	APXBoard* SearchBoard() const;
	
	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* CollisionComponent;

	const float CollisionWidth{31.f};
	const float CollisionDepth{31.f};
	const float CollisionHeight{31.f};
};
