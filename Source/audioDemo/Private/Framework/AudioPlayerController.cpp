// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/AudioPlayerController.h"
#include "Character/PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "UI/PlayerUI.h"

void AAudioPlayerController::OnPossess(APawn* NewPawn)
{
	Super::OnPossess(NewPawn);

	PostPossessionSetup(NewPawn);
}

void AAudioPlayerController::AcknowledgePossession(APawn* NewPawn)
{
	Super::AcknowledgePossession(NewPawn);

	PostPossessionSetup(NewPawn);
}

void AAudioPlayerController::Menu(bool state)
{
	UGameplayStatics::SetGamePaused(GetWorld(), state);
	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(state);
	GetWorld()->GetFirstPlayerController()->bEnableClickEvents = state;

	if (state)
	{
		MenuUI->AddToViewport();
	}
	else
	{
		MenuUI->RemoveFromParent();
	}
}

void AAudioPlayerController::PostPossessionSetup(APawn* NewPawn)
{
	PlayerCharacter = Cast<APlayerCharacter>(NewPawn);
	if (!PlayerCharacter)
	{
		UE_LOG(LogTemp, Error, TEXT("Needs PlayerCharacter as Pawn"));
		return;
	}

	SpawnGameplayUI();
}

void AAudioPlayerController::SpawnGameplayUI()
{
	if (!PlayerCharacter)
	{
		UE_LOG(LogTemp, Error, TEXT("%s, missing gameplayUI class"), *GetName());
		return;
	}

	//returns true if it's a player on the local side of you playing
	if (!IsLocalPlayerController())
	{
		return;
	}

	MenuUI = CreateWidget<UPlayerUI>(this, MenuWidgetClass);

	if (MenuUI == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("%s, missing inventory"), *GetName());
		return;
	}

	MenuUI->AddToViewport();
	MenuUI->RemoveFromParent();
}

void AAudioPlayerController::ChangeMicrophoneVolume(float newVolume)
{
	MenuUI->AdjustMicVolume(newVolume);
}
