// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/IndicatorArrow.h"
#include "Components/Image.h"
#include <cmath>
#include "Components/RadialSlider.h"

void UIndicatorArrow::NativeConstruct()
{

}

float UIndicatorArrow::Rotate(float value)
{
	float mappedValue = (value + 180.0f) / 360.0f;
	if (mappedValue > 1.0f)
	{
		mappedValue -= 1.0f;
	}
	if (mappedValue < 0.0f)
	{
		mappedValue += 1.0f;
	}


	//UE_LOG(LogTemp, Error, TEXT("%f, direction"), mappedValue);

	indicatorSlider->SetValue(mappedValue);
	timeLeft -= 0.1f;


	float valueLeft = (timeLeft / maxTime);
	FSliderStyle* sliderStyle = &indicatorSlider->WidgetStyle;
	sliderStyle->NormalThumbImage.TintColor = FSlateColor(FLinearColor(1, 1, 1, valueLeft));

	return timeLeft;
}



void UIndicatorArrow::SetTime(float time)
{
	FSliderStyle* sliderStyle = &indicatorSlider->WidgetStyle;
	sliderStyle->NormalThumbImage.TintColor = FSlateColor(FLinearColor(1, 1, 1, 1));

	maxTime = time;
	timeLeft = time;
}
