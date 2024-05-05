// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerUI.generated.h"

/**
 * 
 */
UCLASS()
class UPlayerUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// Begin play
	virtual void NativeConstruct() override;

	UFUNCTION()
	void Quit();

	UFUNCTION()
	void AdjustMicVolume(float newValue);

	UPROPERTY(meta = (BindWidget))
	class UButton* quitButton;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* micVolume;

	//UPROPERTY(meta = (BindWidget))
	//class UVolumeSlider* masterSlider;

	//UPROPERTY(meta = (BindWidget))
	//class UVolumeSlider* musicSlider;
	
	//UPROPERTY(meta = (BindWidget))
	//class UVolumeSlider* SFXSlider;
};
