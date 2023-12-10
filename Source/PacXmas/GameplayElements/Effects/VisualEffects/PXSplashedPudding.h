// Copyright (c) 2023 Santa Claus. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PXSplashedPudding.generated.h"

class UPXSplashedPuddingDA;
class UPaperSpriteComponent;

UCLASS()
class PACXMAS_API APXSplashedPudding : public AActor
{
	GENERATED_BODY()

public:
	APXSplashedPudding();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

public:
	void SetActorRotationBasedOnSweepResult(const FHitResult& SweepResult);
	void SetActorLocationBasedOnSweepResult(const FHitResult& SweepResult, const float& Offset);

private:
	UPROPERTY(EditDefaultsOnly)
	UPaperSpriteComponent* PaperSpriteComponent{nullptr};

	UPROPERTY(EditDefaultsOnly, Category="DataAsset")
	UPXSplashedPuddingDA* SplashedPuddingDA{nullptr};
};
