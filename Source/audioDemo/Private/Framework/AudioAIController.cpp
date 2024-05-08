// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/AudioAIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Character/PlayerCharacter.h"

AAudioAIController::AAudioAIController()
{
	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>("AI Perception Component");
	HearingConfig = CreateDefaultSubobject<UAISenseConfig_Hearing>("Hearing Config");

	HearingConfig->DetectionByAffiliation.bDetectEnemies = true;
	HearingConfig->DetectionByAffiliation.bDetectNeutrals = true;
	HearingConfig->DetectionByAffiliation.bDetectFriendlies = true;

	AIPerceptionComponent->ConfigureSense(*HearingConfig);

}

void AAudioAIController::BeginPlay()
{
	Super::BeginPlay();

	AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AAudioAIController::PerceptionUpdated);
}

void AAudioAIController::PerceptionUpdated(AActor* Target, FAIStimulus Stimulus)
{
	UE_LOG(LogTemp, Error, TEXT("Heard something"));
}

void AAudioAIController::PerceptionForgotten(AActor* Target)
{
}
