// Copyright (c) 2023 Smoking Carrots. All rights reserved.


#include "PXCharacterAppearanceComponent.h"

UPXCharacterAppearanceComponent::UPXCharacterAppearanceComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UPXCharacterAppearanceComponent::BeginPlay()
{
	Super::BeginPlay();
}


void UPXCharacterAppearanceComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                                    FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}
