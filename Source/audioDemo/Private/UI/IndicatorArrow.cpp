// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/IndicatorArrow.h"
#include "Components/Image.h"

void UIndicatorArrow::NativeConstruct()
{



}

void UIndicatorArrow::Rotate(float value)
{
	indicatorArrow->SetRenderTransformAngle(value);
}
