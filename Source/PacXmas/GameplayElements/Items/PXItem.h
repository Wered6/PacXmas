// Copyright (c) 2023 Smoking Carrots. All rights reserved.

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

protected:
	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                            UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep,
	                            const FHitResult& SweepResult);

	virtual void CollectItem(APXPlayer* PlayerCharacter);

private:
	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* CollisionComponent{nullptr};
	UPROPERTY(EditDefaultsOnly)
	UPaperSpriteComponent* PaperSpriteComponent{nullptr};

	UPROPERTY(EditDefaultsOnly, Category="DataAsset")
	UPXItemDA* ItemDA{nullptr};

	const float CollisionSize{31.f};
};
