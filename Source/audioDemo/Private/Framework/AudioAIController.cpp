// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/AudioAIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Audio/AudioResponsiveCharacter.h"
#include "Perception/AIPerceptionTypes.h"
#include "Character/PlayerCharacter.h"

AAudioAIController::AAudioAIController()
{
	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>("AI Perception Component");
	HearingConfig = CreateDefaultSubobject<UAISenseConfig_Hearing>("Hearing Config");

	HearingConfig->DetectionByAffiliation.bDetectEnemies = true;
	HearingConfig->DetectionByAffiliation.bDetectNeutrals = true;
	HearingConfig->DetectionByAffiliation.bDetectFriendlies = true;

	AIPerceptionComponent->ConfigureSense(*HearingConfig);

	AIPerceptionComponent->SetDominantSense(UAISense_Hearing::StaticClass());

}

void AAudioAIController::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Error, TEXT("Init One"));

	AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AAudioAIController::PerceptionUpdated);
}

void AAudioAIController::PerceptionUpdated(AActor* Target, FAIStimulus Stimulus)
{
	AAudioResponsiveCharacter* myCharacter = Cast<AAudioResponsiveCharacter>(GetPawn());
	if (myCharacter)
	{
		myCharacter->RecievePerception(Target, Stimulus);
	}
}

void AAudioAIController::PerceptionForgotten(AActor* Target)
{

}
