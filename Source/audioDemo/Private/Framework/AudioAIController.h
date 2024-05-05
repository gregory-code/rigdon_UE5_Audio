// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AudioAIController.generated.h"

/**
 * 
 */
UCLASS()
class AAudioAIController : public AAIController
{
	GENERATED_BODY()

public:
	AAudioAIController();

	virtual void BeginPlay() override;
	
private:

	UPROPERTY(VisibleDefaultsOnly, Category = "AI")
	class UAIPerceptionComponent* AIPerceptionComponent;

	UPROPERTY(VisibleDefaultsOnly, Category = "AI")
	class UAISenseConfig_Hearing* HearingConfig;

	UFUNCTION()
	void PerceptionUpdated(AActor* Target, FAIStimulus Stimulus);

	UFUNCTION()
	void PerceptionForgotten(AActor* Target);
};
