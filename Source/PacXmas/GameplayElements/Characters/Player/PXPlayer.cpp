// Copyright (c) 2023 Santa Claus. All rights reserved.


#include "PXPlayer.h"

// Sets default values
APXPlayer::APXPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APXPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APXPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APXPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

