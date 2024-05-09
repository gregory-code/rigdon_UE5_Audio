// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MicUI.h"
#include "Components/Slider.h"
#include "Components/TextBlock.h"
#include "UI/IndicatorArrow.h"
#include "Components/Button.h"
#include "Components/ProgressBar.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

void UMicUI::NativeConstruct()
{


}


void UMicUI::AdjustMicVolume(float newValue)
{
	micVolume->SetPercent(newValue);

}
