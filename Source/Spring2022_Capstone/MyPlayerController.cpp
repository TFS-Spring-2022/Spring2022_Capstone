// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "GameFramework/FloatingPawnMovement.h"

// Sets default values
AMyPlayerController::AMyPlayerController()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
}
void AMyPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	MyCharacter = Cast<ABaseCharacter>(InPawn);
}

// Called every frame
void AMyPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyPlayerController::SetupInputComponent()
 {
	Super::SetupInputComponent();

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AMyPlayerController::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &AMyPlayerController::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMyPlayerController::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMyPlayerController::Look);
		
		//Crouching
		EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Triggered, this, &AMyPlayerController::Crouch);
		EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Completed, this, &AMyPlayerController::UnCrouch);
		
		//Sprinting
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Triggered, this, &AMyPlayerController::StartSprint);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &AMyPlayerController::StopSprint);

	}

}
void AMyPlayerController::Jump(const FInputActionValue& Value)
{
	MyCharacter->Jump();
}
void AMyPlayerController::StopJumping(const FInputActionValue& Value)
{
	MyCharacter->StopJumping();
}
void AMyPlayerController::Move(const FInputActionValue& Value)
{
	MyCharacter->Move(Value);
}
void AMyPlayerController::Look(const FInputActionValue& Value)
{
	MyCharacter->Look(Value);
}
void AMyPlayerController::Crouch(const FInputActionValue& Value)
{
	MyCharacter->StartCrouch();
}
void AMyPlayerController::UnCrouch(const FInputActionValue& Value)
{
	MyCharacter->StopCrouch();
}
void AMyPlayerController::StartSprint(const FInputActionValue& Value)
{
	MyCharacter->StartSprint();
}
void AMyPlayerController::StopSprint(const FInputActionValue& Value)
{
	MyCharacter->StopSprint();
}