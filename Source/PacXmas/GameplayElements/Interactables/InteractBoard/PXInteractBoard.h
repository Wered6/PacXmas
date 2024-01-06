// Copyright (c) 2023 Smoking Carrots. All rights reserved.

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
	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                            UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep,
	                            const FHitResult& SweepResult);

private:
	APXBoard* FindBoard() const;

	UPROPERTY()
	UBoxComponent* CollisionComponent;

	const float CollisionSize{31.f};
};
