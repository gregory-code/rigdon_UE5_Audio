// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PlayerCharacter.h"
#include "GameFramework/SpringArmComponent.h" // have to include headers
#include "Camera/CameraComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "Framework/AudioPlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	cameraBoom = CreateDefaultSubobject<USpringArmComponent>("Camera Boom");
	viewCamera = CreateDefaultSubobject<UCameraComponent>("View Camera");
	//inventoryComp = CreateDefaultSubobject<UInventoryComponent>("Inventory Component"); need the inventory component

	cameraBoom->SetupAttachment(GetRootComponent());
	viewCamera->SetupAttachment(cameraBoom, USpringArmComponent::SocketName);

	cameraBoom->bUsePawnControlRotation = true;
	cameraBoom->TargetArmLength = 0.0f;

	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(1080.0f);

	GetCharacterMovement()->JumpZVelocity = 600.0f;
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	menuInputAction->bTriggerWhenPaused = true;

	FInputModeGameOnly input;
	GetWorld()->GetFirstPlayerController()->SetInputMode(input);

	MyPlayerController = Cast<AAudioPlayerController>(GetController());
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