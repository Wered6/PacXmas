// Copyright (c) 2023 Smoking Carrots. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PXCharacterAppearanceComponent.generated.h"

class UPXCharacterDA;
class UPaperFlipbookComponent;

UCLASS()
class PACXMAS_API UPXCharacterAppearanceComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPXCharacterAppearanceComponent();

protected:
	virtual void BeginPlay() override;

	virtual void OnRegister() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

public:
	void UpdateFlipbookToDirection(const FVector& Direction) const;

	virtual void SetFlipbookIdle() const;

protected:
	UPROPERTY()
	UPXCharacterDA* PXCharacterDA{nullptr};

	UPROPERTY()
	UPaperFlipbookComponent* FlipbookComponent{nullptr};
};
