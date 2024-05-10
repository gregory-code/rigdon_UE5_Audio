// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PlayerCharacter.h"
#include "GameFramework/SpringArmComponent.h" // have to include headers
#include "Camera/CameraComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "UI/IndicatorArrow.h"
#include "Framework/AudioPlayerController.h"
#include "AudioDevice.h"
#include "AudioCaptureComponent.h"
#include "Components/AudioComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AIPerceptionTypes.h"
#include "Perception/AISense_Hearing.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Framework/AudioAIController.h"
#include "Audio/AudioResponsiveCharacter.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	cameraBoom = CreateDefaultSubobject<USpringArmComponent>("Camera Boom");
	viewCamera = CreateDefaultSubobject<UCameraComponent>("View Camera");
	//inventoryComp = CreateDefaultSubobject<UInventoryComponent>("Inventory Component"); need the inventory component

	audioCapture = CreateDefaultSubobject<UAudioCaptureComponent>("Audio Capture");
	audioCapture->bAutoActivate = true;
	audioCapture->bEnableBaseSubmix = false;
	audioCapture->bIsUISound = true;

	audioCapture->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);

	cameraBoom->SetupAttachment(GetRootComponent());
	viewCamera->SetupAttachment(cameraBoom, USpringArmComponent::SocketName);

	cameraBoom->bUsePawnControlRotation = true;
	cameraBoom->TargetArmLength = 0.0f;

	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(1080.0f);

	GetCharacterMovement()->JumpZVelocity = 600.0f;
}

void APlayerCharacter::RecievePerception(AActor* Target, FAIStimulus Stimulus)
{
	for (FVector stimulus : stimulusLocations)
	{
		if (Stimulus.StimulusLocation == stimulus)
		{
			return;
		}
	}
	stimulusLocations.Add(Stimulus.StimulusLocation);
	MyPlayerController->ManageIndicatorArrow(GetActorLocation(), Stimulus.StimulusLocation);
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	AudioResponsiveCharacter = GetWorld()->SpawnActor<AAudioResponsiveCharacter>(AudioResponsiveCharacterClass, GetActorLocation(), GetActorRotation());
	AudioResponsiveCharacter->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	AudioResponsiveCharacter->SetActorLocation(FVector(0,0,0));
	AudioResponsiveCharacter->SetAsPlayer();

	menuInputAction->bTriggerWhenPaused = true;

	audioCapture->OnAudioEnvelopeValue.AddDynamic(this, &APlayerCharacter::AudioValueChanged);

	FInputModeGameOnly input;
	GetWorld()->GetFirstPlayerController()->SetInputMode(input);

	MyPlayerController = Cast<AAudioPlayerController>(GetController());
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AudioResponsiveCharacter->SetActorRelativeLocation(FVector(0,0,0));

	for (int i = 0; i < stimulusLocations.Num(); i++)
	{
		if (MyPlayerController->MoveArrow(i, GetActorLocation(), stimulusLocations[i]) == true)
		{
			stimulusLocations.RemoveAt(i);
			i--;
		}
	}
}

void APlayerCharacter::PawnClientRestart() // Treating this as begin play ???
{
	Super::PawnClientRestart();

	APlayerController* PlayerController = GetController<APlayerController>();
	if (PlayerController)
	{
		UEnhancedInputLocalPlayerSubsystem* InputSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		InputSystem->ClearAllMappings();
		InputSystem->AddMappingContext(inputMapping, 0);
	}
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* enhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (enhancedInputComponent)
	{
		enhancedInputComponent->BindAction(moveInputAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);
		enhancedInputComponent->BindAction(lookInputAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Look);
		enhancedInputComponent->BindAction(menuInputAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Menu);
	}
}

void APlayerCharacter::Move(const FInputActionValue& InputValue)
{
	FVector2D input = InputValue.Get<FVector2D>();
	input.Normalize();

	AddMovementInput(input.Y * GetMoveFwdDir() + input.X * GetMoveRightDir());
}

void APlayerCharacter::Look(const FInputActionValue& InputValue)
{
	FVector2D input = InputValue.Get<FVector2D>();
	AddControllerYawInput(input.X);
	AddControllerPitchInput(-input.Y);
}

void APlayerCharacter::Menu()
{
	if (MyPlayerController)
	{
		bInMenu = !bInMenu;

		MyPlayerController->Menu(bInMenu);
	}

}

void APlayerCharacter::AudioValueChanged(float newValue)
{
	//UE_LOG(LogTemp, Error, TEXT("%f, Sound"), newValue);

	if (newValue >= 0.4f)
	{
		UE_LOG(LogTemp, Error, TEXT("makin' my sound"));
		UAISense_Hearing::ReportNoiseEvent(GetWorld(), GetActorLocation(), 2, this);
	}


	float roundedValue = FMath::LogX(10, newValue);
	roundedValue = UKismetMathLibrary::MapRangeClamped(roundedValue, inRangeAMicVolume, inRangeBMicVolume, 0.0f, 1.0f);
	MyPlayerController->ChangeMicrophoneVolume(roundedValue);
}


FVector APlayerCharacter::GetMoveFwdDir() const
{
	FVector CameraFwd = viewCamera->GetForwardVector();
	CameraFwd.Z = 0;

	return CameraFwd.GetSafeNormal();
}

FVector APlayerCharacter::GetMoveRightDir() const
{
	return viewCamera->GetRightVector();
}