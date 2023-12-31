// Copyright (c) 2023 Smoking Carrots. All rights reserved.


#include "PXCamera.h"
#include "Camera/CameraComponent.h"
#include "PacXmas/Utilities/CustomLogs/PXCustomLogs.h"

APXCamera::APXCamera()
{
	PrimaryActorTick.bCanEverTick = true;

	UCameraComponent* CameraComp = GetCameraComponent();

	if (!CameraComp)
	{
		UE_LOG(LogCamera, Warning, TEXT("APXCamera::APXCamera|CameraComp is nullptr"));
		return;
	}

	CameraComp->ProjectionMode = ECameraProjectionMode::Orthographic;
	CameraComp->OrthoWidth = 1440.f;
}
