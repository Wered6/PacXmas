// Copyright (c) 2023 Santa Claus. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PXItem.generated.h"

class APXPlayer;
class UBoxComponent;
class UPaperSpriteComponent;
class UPXItemDA;

UCLASS()
class PACXMAS_API APXItem : public AActor
{
	GENERATED_BODY()

public:
	APXItem();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

protected:
	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                            UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep,
	                            const FHitResult& SweepResult);

	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* CollisionComponent{nullptr};

private:
	void CollectItem(APXPlayer* PlayerCharacter);

	UPROPERTY(EditAnywhere, Category="DataAsset")
	UPXItemDA* ItemDA{nullptr};
	UPROPERTY(EditDefaultsOnly)
	UPaperSpriteComponent* PaperSpriteComponent{nullptr};

	const float CollisionWidth{31.f};
	const float CollisionDepth{31.f};
	const float CollisionHeight{31.f};
};
