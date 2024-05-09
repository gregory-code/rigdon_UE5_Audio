// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/AudioPlayerController.h"
#include "Character/PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Perception/AIPerceptionComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "UI/IndicatorArrow.h"
#include "UI/PlayerUI.h"
#include "UI/MicUI.h"

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
	MicUI = CreateWidget<UMicUI>(this, MicWidgetClass);

	if (MenuUI == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("%s, missing inventory"), *GetName());
		return;
	}

	MicUI->AddToViewport();
	MenuUI->AddToViewport();
	MenuUI->RemoveFromParent();
}

void AAudioPlayerController::ManageIndicatorArrow(FVector playerLocation, FVector StimulusLocation)
{
	UIndicatorArrow* arrow = CreateWidget<UIndicatorArrow>(this, arrowClass);
	arrow->AddToViewport();
	currentIndicators.Add(arrow);
}

void AAudioPlayerController::MoveArrow(int index, FVector playerLocation, FVector StimulusLocation)
{
	FRotator rotation = GetControlRotation();
	FRotator lookAt = UKismetMathLibrary::FindLookAtRotation(playerLocation, StimulusLocation);

	float targetScreenLocation = rotation.Yaw - lookAt.Yaw;

	currentIndicators[index]->Rotate(targetScreenLocation * -1);
}

void AAudioPlayerController::ChangeMicrophoneVolume(float newVolume)
{
	MicUI->AdjustMicVolume(newVolume);
}
