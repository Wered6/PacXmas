// Copyright (c) 2023 Smoking Carrots. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "PXClassSubsystem.generated.h"

enum class EPlayerClass : uint8_t
{
	Girl,
	Boy
};

UCLASS()
class PACXMAS_API UPXClassSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	// USubsystem implementation Begin
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;;
	virtual void Deinitialize() override;;
	// USubsystem implementation End

	void SetPlayerClass(const EPlayerClass NewPlayerClass);
	EPlayerClass GetPlayerClass() const;

private:
	EPlayerClass PlayerClass;

	bool bInitialized{false};
};
