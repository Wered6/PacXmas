// Copyright (c) 2023 Smoking Carrots. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "PacXmas/GameplayElements/Characters/AppearanceComponent/PXCharacterAppearanceComponent.h"
#include "PXPlayerAppearanceComponent.generated.h"

class UPXPlayerThrowPuddingDA;
class UPXPlayerDA;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FShootPuddingAnimationEndDelegate);

enum class EPlayerLook : uint8_t
{
	Default,
	Pudding,
	MusicSheet,
	PuddingMusicSheet
};

UCLASS()
class PACXMAS_API UPXPlayerAppearanceComponent : public UPXCharacterAppearanceComponent
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	void SetCurrentDataAsset(const EPlayerLook PlayerLook);
	void SetFlipbookToGameOver();

	FShootPuddingAnimationEndDelegate OnShootPuddingAnimationEnd;

private:
	void BindShootPuddingDelegate();
	UFUNCTION()
	void PlayThrowPuddingAnimation(bool bHasMusicSheet, FVector ActorForwardVector);
	
	void BindShootPuddingFinishedDelegate();
	UFUNCTION()
	void ThrowPuddingAnimationFinished();

	UPXPlayerThrowPuddingDA* ChooseThrowPuddingDA(const bool bHasMusicSheet);

	UPROPERTY()
	UPXPlayerDA* PXPlayerCurrentDA{nullptr};

	UPROPERTY(EditDefaultsOnly, Category="Player Look|Default")
	UPXPlayerDA* PXPlayerDefaultDA{nullptr};
	UPROPERTY(EditDefaultsOnly, Category="Player Look|Pudding")
	UPXPlayerDA* PXPlayerPuddingDA{nullptr};
	UPROPERTY(EditDefaultsOnly, Category="Player Look|Music Sheet")
	UPXPlayerDA* PXPlayerMusicSheetDA{nullptr};
	UPROPERTY(EditDefaultsOnly, Category="Player Look|Pudding And Music Sheet")
	UPXPlayerDA* PXPlayerPuddingMusicSheet{nullptr};

	UPROPERTY(EditDefaultsOnly, Category="Player Shoot Pudding|Pudding")
	UPXPlayerThrowPuddingDA* PXPlayerPuddingThrowPuddingDA{nullptr};
	UPROPERTY(EditDefaultsOnly, Category="Player Shoot Pudding|Pudding And Music Sheet")
	UPXPlayerThrowPuddingDA* PXPlayerPuddingMusicSheetThrowPuddingDA{nullptr};
};
