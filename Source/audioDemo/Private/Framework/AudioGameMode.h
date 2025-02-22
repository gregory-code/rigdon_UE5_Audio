// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "AudioGameMode.generated.h"

/**
 * 
 */
UCLASS()
class AAudioGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, Category = "Sound")
	class USoundWave* titleSong;

protected:
	virtual void BeginPlay() override;
};
