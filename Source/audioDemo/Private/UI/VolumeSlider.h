// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "VolumeSlider.generated.h"

/**
 * 
 */
UCLASS()
class UVolumeSlider : public UUserWidget
{
	GENERATED_BODY()
	
public:

	virtual void NativeConstruct() override;

	UFUNCTION()
	void ValueChanged(float newValue);

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	class USoundMix* SoundMixerClass;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	class USoundClass* SoundClass;

	UPROPERTY(meta = (BindWidget))
	class USlider* volumeSlider;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* sliderProgress;
};
