// Copyright (c) 2023 Santa Claus. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PXAppearanceComponent.generated.h"

enum class EPlayerLook;

UENUM()
enum class ECharacterDirection : uint8
{
	Idle,
	Up,
	Right,
	Down,
	Left
};

UENUM()
enum class EAxisMovement
{
	Vertical,
	Horizontal
};

class UPXCharacterDA;
class UPaperFlipbookComponent;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PACXMAS_API UPXAppearanceComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPXAppearanceComponent();

protected:
	virtual void BeginPlay() override;

	virtual void OnRegister() override;

public:
	void SetFlipbookBasedOnAxis(const int8 Sign, const EAxisMovement Axis) const;
	void SetFlipbookBasedOnDirection(const ECharacterDirection Direction) const;

protected:
	UPROPERTY()
	UPXCharacterDA* ActiveDA{nullptr};
	UPROPERTY(EditDefaultsOnly, Category="DataAssets|Default")
	UPXCharacterDA* CharacterDA{nullptr};

	UPROPERTY()
	UPaperFlipbookComponent* FlipbookComponent{nullptr};
};
