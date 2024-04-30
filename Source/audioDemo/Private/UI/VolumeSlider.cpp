// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/VolumeSlider.h"
#include "Components/Slider.h"
#include "Kismet/GameplayStatics.h"

void UVolumeSlider::NativeConstruct()
{
	volumeSlider->OnValueChanged.AddDynamic(this, &UVolumeSlider::ValueChanged);
}

void UVolumeSlider::ValueChanged(float newValue)
{
	UGameplayStatics::SetSoundMixClassOverride(GetWorld(), SoundMixerClass, SoundClass, newValue, 1.0f, 0.0f);
	UGameplayStatics::PushSoundMixModifier(GetWorld(), SoundMixerClass);
}
