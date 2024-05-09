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

	void Rotate(float value);

	UPROPERTY(meta = (BindWidget))
	class URadialSlider* indicatorSlider;
};
