// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Framework/AudioPlayerController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AIPerceptionTypes.h"
#include "Perception/AISense_Hearing.h"
#include "PlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
class AAudioPlayerController;

UCLASS()
class APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	APlayerCharacter();

	AAudioPlayerController* MyPlayerController;

	void RecievePerception(AActor* Target, FAIStimulus Stimulus);

private:
	UPROPERTY(EditDefaultsOnly, Category = "View")
	TSubclassOf<class AAudioResponsiveCharacter> AudioResponsiveCharacterClass;

	UPROPERTY(visibleAnywhere, Category = "View")
	class AAudioResponsiveCharacter* AudioResponsiveCharacter;

	UPROPERTY(visibleAnywhere, Category = "View")
	USpringArmComponent* cameraBoom;

	UPROPERTY(visibleAnywhere, Category = "View")
	UCameraComponent* viewCamera;

	UPROPERTY(visibleAnywhere, Category = "Audio")
	class UAudioCaptureComponent* audioCapture;

	UPROPERTY(EditAnywhere, Category = "Audio")
	float inRangeAMicVolume = -2.7f;
	UPROPERTY(EditAnywhere, Category = "Audio")
	float inRangeBMicVolume = -0.7f;

	//UPROPERTY(visibleAnywhere, Category = "Inventory")
	//UInventoryComponent* inventoryComp;

	virtual void PawnClientRestart() override;

	/********************************************/
	/*                Input                     */
	/********************************************/
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputMappingContext* inputMapping;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* moveInputAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* lookInputAction;

	UPROPERTY(EditDefaultsOnly, Category = "Menu")
	UInputAction* menuInputAction;


	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void Move(const FInputActionValue& InputValue);

	UFUNCTION()
	void Look(const FInputActionValue& InputValue);

	UFUNCTION()
	void Menu();

	UFUNCTION()
	void AudioValueChanged(float newValue);

	bool bInMenu;

	FVector GetMoveFwdDir() const;
	FVector GetMoveRightDir() const;

};
