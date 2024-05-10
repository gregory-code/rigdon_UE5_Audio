// Fill out your copyright notice in the Description page of Project Settings.


#include "Audio/AudioResponsiveCharacter.h"
#include "Engine/World.h"
#include "Character/PlayerCharacter.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AIPerceptionTypes.h"
#include "Perception/AISense_Hearing.h"
#include "Kismet/GameplayStatics.h"
#include "Framework/AudioAIController.h"

// Sets default values
AAudioResponsiveCharacter::AAudioResponsiveCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAudioResponsiveCharacter::BeginPlay()
{
	Super::BeginPlay();

	for (int32 i = 0; i < PoolSize; i++)
	{
		UAudioComponent* audioComponent = NewObject<UAudioComponent>(this);
		audioComponent->RegisterComponent();
		audioComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
		AudioSourcePool.Add(audioComponent);
	}
	
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AAudioResponsiveCharacter::IndicateNoise, 8, false);
}

// Called every frame
void AAudioResponsiveCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

void AAudioResponsiveCharacter::SetAsPlayer()
{
	AAIController* defaultController = Cast<AAIController>(GetController());
	AAudioAIController* myController = Cast<AAudioAIController>(defaultController);

	TArray<AActor*> outActors;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), playerClass, outActors);
	for (AActor* actor : outActors)
	{
		myPlayer = Cast<APlayerCharacter>(actor);
		if (myPlayer)
		{
			UE_LOG(LogTemp, Error, TEXT("Is Player"));
			isPlayer = true;
		}
	}
}

void AAudioResponsiveCharacter::RecievePerception(AActor* Target, FAIStimulus Stimulus)
{
	if (Stimulus.StimulusLocation == GetActorLocation())
	{
		return;
	}

	if (isPlayer)
	{
		//UE_LOG(LogTemp, Error, TEXT("%sheard something"), *GetPawn()->GetName());
		myPlayer->RecievePerception(Target, Stimulus);
		//UE_LOG(LogTemp, Error, TEXT("Player heard something"));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("makin' my sound"));
		SpawnAudio();
		//UE_LOG(LogTemp, Error, TEXT("Environment heard something"));
	}
}


void AAudioResponsiveCharacter::SpawnAudio()
{
	if (soundCollection.Num() <= 0)
		return;

	int32 index = FMath::RandRange(0, soundCollection.Num() - 1);
	USoundBase* sound = soundCollection[index];

	if (sound == nullptr)
		return;

	UAudioComponent* availableAudioSource = GetAvailableAudioSourceComponent();

	if (availableAudioSource == nullptr)
		return;

	availableAudioSource->SetSound(sound);
	FVector spawnLocation = GetActorLocation();
	availableAudioSource->SetWorldLocation(spawnLocation);
	availableAudioSource->Play();
}

// Called to bind functionality to input
void AAudioResponsiveCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AAudioResponsiveCharacter::IndicateNoise()
{
	if (isPlayer == false)
	{
		//UAISense_Hearing::ReportNoiseEvent(GetWorld(), GetActorLocation(), 1, this);

		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AAudioResponsiveCharacter::IndicateNoise, 8, false);
	}
}

UAudioComponent* AAudioResponsiveCharacter::GetAvailableAudioSourceComponent()
{
	for (UAudioComponent* audioSource : AudioSourcePool)
	{
		if (!audioSource->IsPlaying())
		{
			return audioSource;
		}
	}
	return nullptr;
}

