// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AudioPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class AAudioPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	// This function calls only on the server
	virtual void OnPossess(APawn* NewPawn) override;

	// This function calls on both the listening server, and the client
	virtual void AcknowledgePossession(APawn* NewPawn) override;

	UFUNCTION()
	void Menu(bool state);

	UFUNCTION()
	void ChangeMicrophoneVolume(float newVolume);

	UFUNCTION()
	void ManageIndicatorArrow(FVector playerLocation, FVector StimulusLocation);

	UFUNCTION()
	void MoveArrow(int index, FVector playerLocation, FVector StimulusLocation);

private:
	void PostPossessionSetup(APawn* NewPawn);

	void SpawnGameplayUI();

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<class UIndicatorArrow> arrowClass;

	UPROPERTY()
	TArray<class UIndicatorArrow*> currentIndicators;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<class UPlayerUI> MenuWidgetClass;

	UPROPERTY()
	UPlayerUI* MenuUI;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<class UMicUI> MicWidgetClass;

	UPROPERTY()
	UMicUI* MicUI;

	UPROPERTY()
	class APlayerCharacter* PlayerCharacter;
};
