// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AIPerceptionTypes.h"
#include "Components/AudioComponent.h"
#include "Perception/AISense_Hearing.h"
#include "AudioResponsiveCharacter.generated.h"

UCLASS()
class AAudioResponsiveCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAudioResponsiveCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetAsPlayer();

	UPROPERTY(EditAnywhere, Category = "Audio")
	TArray<USoundBase*> soundCollection;

	UPROPERTY(EditAnywhere, Category = "Audio", meta = (ClampMin = "1", UIMin = "1"))
	int32 PoolSize = 1;

	void RecievePerception(AActor* Target, FAIStimulus Stimulus);

	UPROPERTY(EditDefaultsOnly, Category = "View")
	TSubclassOf<class APlayerCharacter> playerClass;

	class APlayerCharacter* myPlayer;

	UFUNCTION()
	void SpawnAudio();

	UPROPERTY(visibleAnywhere, Category = "View")
	bool isPlayer;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	FTimerHandle TimerHandle;

	void IndicateNoise();

	TArray<UAudioComponent*> AudioSourcePool;

	UAudioComponent* GetAvailableAudioSourceComponent();
};
