// Copyright (c) 2023 Smoking Carrots. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PXCharacterAppearanceComponent.generated.h"

class UPXCharacterMovementComponent;
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
	void InitializeMovementComponent(UPXCharacterMovementComponent* MovementComponent);

protected:
	UFUNCTION()
	void SetFlipbookIdle();
	UFUNCTION()
	void UpdateFlipbookToDirection(const FVector& Direction);
	
	UPROPERTY()
	UPXCharacterDA* PXCharacterDA{nullptr};

	UPROPERTY()
	UPaperFlipbookComponent* FlipbookComponent{nullptr};

private:
	void BindChangeStateDelegates();

	UPROPERTY()
	UPXCharacterMovementComponent* PXCharacterMovementComponent{nullptr};
};
