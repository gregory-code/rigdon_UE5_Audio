// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MicUI.generated.h"

/**
 * 
 */
UCLASS()
class UMicUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// Begin play
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* micVolume;

	UFUNCTION()
	void AdjustMicVolume(float newValue);
};
