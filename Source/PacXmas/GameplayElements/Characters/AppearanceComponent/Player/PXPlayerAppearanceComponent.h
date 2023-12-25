// Copyright (c) 2023 Santa Claus. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "PXPlayerAppearanceComponent.generated.h"

class UPaperFlipbookComponent;
class UPXPlayerDA;

enum class EPlayerLook : int
{
	Default,
	Pudding,
	MusicSheet,
	PuddingMusicSheet
};

UCLASS()
class PACXMAS_API UPXPlayerAppearanceComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPXPlayerAppearanceComponent();

	void SetCurrentDataAsset(const EPlayerLook PlayerLook);
	void SetFlipbookBasedOnActorForwardVector(const FVector& ActorForwardVector) const;
	void SetFlipbookIdle() const;

protected:
	virtual void BeginPlay() override;

	virtual void OnRegister() override;

private:
	UPROPERTY()
	UPXPlayerDA* PlayerCurrentDA{nullptr};

	UPROPERTY(EditDefaultsOnly, Category="Player Look|Default")
	UPXPlayerDA* PlayerDefaultDA{nullptr};
	UPROPERTY(EditDefaultsOnly, Category="Player Look|Pudding")
	UPXPlayerDA* PlayerPuddingDA{nullptr};
	UPROPERTY(EditDefaultsOnly, Category="Player Look|Music Sheet")
	UPXPlayerDA* PlayerMusicSheetDA{nullptr};
	UPROPERTY(EditDefaultsOnly, Category="Player Look|Pudding And Music Sheet")
	UPXPlayerDA* PlayerPuddingMusicSheet{nullptr};

	UPROPERTY()
	UPaperFlipbookComponent* FlipbookComponent{nullptr};
};
