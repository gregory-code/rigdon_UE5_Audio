// Fill out your copyright notice in the Description page of Project Settings.


#include "Audio/AudioSpawner.h"
#include "Engine/World.h"
#include "Perception/AISense_Hearing.h"

// Sets default values
AAudioSpawner::AAudioSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAudioSpawner::BeginPlay()
{
	Super::BeginPlay();

	for (int32 i = 0; i < PoolSize; i++)
	{
		UAudioComponent* audioComponent = NewObject<UAudioComponent>(this);
		audioComponent->RegisterComponent();
		audioComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
		AudioSourcePool.Add(audioComponent);
	}
	
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AAudioSpawner::SpawnAudio, SpawnTime, false);
	GetWorld()->GetTimerManager().SetTimer(NoiseHandle, this, &AAudioSpawner::CreateNoise, 2, false);
}

// Called every frame
void AAudioSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAudioSpawner::SpawnAudio()
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

	UAISense_Hearing::ReportNoiseEvent(GetWorld(), GetActorLocation(), 1, this);

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AAudioSpawner::SpawnAudio, SpawnTime, false);
}

void AAudioSpawner::CreateNoise()
{
	UE_LOG(LogTemp, Error, TEXT("Creating noise"));
	UAISense_Hearing::ReportNoiseEvent(GetWorld(), GetActorLocation(), 1.5f, this);
	GetWorld()->GetTimerManager().SetTimer(NoiseHandle, this, &AAudioSpawner::CreateNoise, 2, false);
}

UAudioComponent* AAudioSpawner::GetAvailableAudioSourceComponent()
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

