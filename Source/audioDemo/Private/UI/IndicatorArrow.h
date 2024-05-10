// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "IndicatorArrow.generated.h"

/**
 * 
 */
UCLASS()
class UIndicatorArrow : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// Begin play
	virtual void NativeConstruct() override;

	float Rotate(float value);

	void SetTime(float time);

	UPROPERTY()
	float timeLeft;

	UPROPERTY()
	float maxTime;

	UPROPERTY(meta = (BindWidget))
	class URadialSlider* indicatorSlider;
};
