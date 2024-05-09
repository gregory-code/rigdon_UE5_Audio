// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/IndicatorArrow.h"
#include "Components/Image.h"
#include <cmath>
#include "Components/RadialSlider.h"

void UIndicatorArrow::NativeConstruct()
{

}

void UIndicatorArrow::Rotate(float value)
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

	//float mappedValue = fmod(value + 180.0f, 360.0f);
	//mappedValue /= 360;
	UE_LOG(LogTemp, Error, TEXT("%f, direction"), mappedValue);

	indicatorSlider->SetValue(mappedValue);
	
}
