// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/AudioComponent.h"
#include "AudioSpawner.generated.h"

UCLASS()
class AAudioSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAudioSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Audio")
	TArray<USoundBase*> soundCollection;

	UPROPERTY(EditAnywhere, Category = "Audio", meta = (ClampMin = "1", UIMin = "1"))
	int32 PoolSize = 1;

	UFUNCTION()
	void SpawnAudio();

	UPROPERTY(EditAnywhere, Category = "Audio")
	float SpawnTime = 0.5f;

private:
	FTimerHandle TimerHandle;

	TArray<UAudioComponent*> AudioSourcePool;

	UAudioComponent* GetAvailableAudioSourceComponent();
};
