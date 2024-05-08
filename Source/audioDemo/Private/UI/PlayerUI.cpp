// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PlayerUI.h"
#include "Components/Slider.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/ProgressBar.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Character/PlayerCharacter.h"


void UPlayerUI::NativeConstruct()
{
	Super::NativeConstruct();

	quitButton->OnClicked.AddDynamic(this, &UPlayerUI::Quit);
}

void UPlayerUI::Quit()
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController)
	{
		UKismetSystemLibrary::QuitGame(GetWorld(), PlayerController, EQuitPreference::Quit, true);
	}
}
