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
	UGameplayStatics::SetSoundMixClassOverride(GetWorld(), SoundMixerClass, SoundClass, newValue);
	UGameplayStatics::PushSoundMixModifier(GetWorld(), SoundMixerClass);
}
