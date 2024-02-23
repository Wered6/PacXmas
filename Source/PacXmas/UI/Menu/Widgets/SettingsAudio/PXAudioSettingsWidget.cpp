// Copyright (c) 2023 Smoking Carrots. All rights reserved.


#include "PXAudioSettingsWidget.h"
#include "Components/Slider.h"
#include "Components/TextBlock.h"
#include "Kismet/KismetMathLibrary.h"
#include "PacXmas/Subsystems/AudioSubsystem/PXAudioMixer.h"
#include "PacXmas/Utilities/CustomLogs/PXCustomLogs.h"

void UPXAudioSettingsWidget::NativeConstruct()
{
	Super::NativeConstruct();

	InitializeAudioMixer();

	LoadAudioSettings();

	SetVolumeTextBasedOnSlider(MusicSlider, MusicVolumeText);
	SetVolumeTextBasedOnSlider(SFXSlider, SFXVolumeText);
}

void UPXAudioSettingsWidget::OnMusicSliderValueChanged() const
{
	ApplyVolumeChange(MusicSlider);
}

void UPXAudioSettingsWidget::OnSFXSliderValueChanged() const
{
	ApplyVolumeChange(SFXSlider);
}

void UPXAudioSettingsWidget::OnMusicVolumeMinusButtonClicked() const
{
	AdjustVolume(MusicSlider, MusicVolumeStep, false);
}

void UPXAudioSettingsWidget::OnSFXVolumeMinusButtonClicked() const
{
	AdjustVolume(SFXSlider, SFXVolumeStep, false);
}

void UPXAudioSettingsWidget::OnMusicVolumePlusButtonClicked() const
{
	AdjustVolume(MusicSlider, MusicVolumeStep, true);
}

void UPXAudioSettingsWidget::OnSFXVolumePlusButtonClicked() const
{
	AdjustVolume(SFXSlider, SFXVolumeStep, true);
}

void UPXAudioSettingsWidget::InitializeAudioMixer()
{
	if (!PXAudioMixerClass)
	{
		UE_LOG(LogClass, Warning,
		       TEXT("UPXAudioSettingsWidget::InitializeAudioMixer|PXAudioMixerClass is nullptr"))
		return;
	}

	PXAudioMixer = NewObject<UPXAudioMixer>(this, PXAudioMixerClass);
}

void UPXAudioSettingsWidget::AdjustVolume(USlider* Slider, const float VolumeStep, const bool bIncrease) const
{
	if (!Slider)
	{
		UE_LOG(LogWidget, Warning, TEXT("UPXAudioSettingsWidget::AdjustVolume|Slider is nullptr"))
		return;
	}

	float NewVolume;

	if (bIncrease)
	{
		NewVolume = Slider->GetValue() + VolumeStep;
	}
	else
	{
		NewVolume = Slider->GetValue() - VolumeStep;
	}

	NewVolume = FMath::Clamp(NewVolume, 0.f, 1.f);
	Slider->SetValue(NewVolume);

	ApplyVolumeChange(Slider);
}

void UPXAudioSettingsWidget::ApplyVolumeChange(const USlider* Slider) const
{
	if (!Slider)
	{
		UE_LOG(LogSound, Warning, TEXT("UPXAudioSettingsWidget::ApplyVolumeChange|Slider is nullptr"))
		return;
	}
	if (!PXAudioMixer)
	{
		UE_LOG(LogSound, Warning, TEXT("UPXAudioSettingsWidget::ApplyVolumeChange|PXAudioMixer is nullptr"))
		return;
	}
	if (!MusicSlider)
	{
		UE_LOG(LogWidget, Warning, TEXT("UPXAudioSettingsWidget::ApplyVolumeChange|MusicSlider is nullptr"))
		return;
	}
	if (!SFXSlider)
	{
		UE_LOG(LogWidget, Warning, TEXT("UPXAudioSettingsWidget::ApplyVolumeChange|SFXSlider is nullptr"))
		return;
	}

	if (Slider == MusicSlider)
	{
		const float MusicVolume = Slider->GetValue();
		PXAudioMixer->SetMusicSoundClassVolume(MusicVolume);
		SetVolumeTextBasedOnSlider(MusicSlider, MusicVolumeText);
	}
	else if (Slider == SFXSlider)
	{
		const float SFXVolume = Slider->GetValue();
		PXAudioMixer->SetSFXSoundClassVolume(SFXVolume);
		SetVolumeTextBasedOnSlider(SFXSlider, SFXVolumeText);
	}

	SaveAudioSettings();
}

void UPXAudioSettingsWidget::SetVolumeTextBasedOnSlider(const USlider* Slider, UTextBlock* VolumeText) const
{
	if (!Slider)
	{
		UE_LOG(LogWidget, Warning, TEXT("UPXAudioSettingsWidget::SetVolumeTextBasedOnSlider|Slider is nullptr"))
		return;
	}
	if (!VolumeText)
	{
		UE_LOG(LogWidget, Warning, TEXT("UPXAudioSettingsWidget::SetVolumeTextBasedOnSlider|VolumeText is nullptr"))
		return;
	}

	const float SliderValue = UKismetMathLibrary::Round(Slider->GetValue() * 100);
	VolumeText->SetText(FText::AsNumber(SliderValue));
}

void UPXAudioSettingsWidget::SaveAudioSettings() const
{
	if (!MusicSlider)
	{
		UE_LOG(LogWidget, Warning, TEXT("UPXAudioSettingsWidget::SaveAudioSettings|MusicSlider is nullptr"))
		return;
	}
	if (!SFXSlider)
	{
		UE_LOG(LogWidget, Warning, TEXT("UPXAudioSettingsWidget::SaveAudioSettings|SFXSlider is nullptr"))
		return;
	}

	const float MusicVolume = MusicSlider->GetValue();
	const float SFXVolume = SFXSlider->GetValue();

	PXAudioMixer->SaveAudioSettings(MusicVolume, SFXVolume);
}

void UPXAudioSettingsWidget::LoadAudioSettings() const
{
	if (!PXAudioMixer)
	{
		UE_LOG(LogSound, Warning, TEXT("UPXAudioSettingsWidget::LoadAudioSettings|PXAudioMixer is nullptr"))
		return;
	}
	if (!MusicSlider)
	{
		UE_LOG(LogWidget, Warning, TEXT("UPXAudioSettingsWidget::LoadAudioSettings|MusicSLider is nullptr"))
		return;
	}
	if (!SFXSlider)
	{
		UE_LOG(LogWidget, Warning, TEXT("UPXAudioSettingsWidget::LoadAudioSettings|SFXSlider is nullptr"))
		return;
	}

	float MusicVolume;
	float SFXVolume;

	PXAudioMixer->LoadAudioSettings(MusicVolume, SFXVolume);

	MusicSlider->SetValue(MusicVolume);
	SFXSlider->SetValue(SFXVolume);
}
