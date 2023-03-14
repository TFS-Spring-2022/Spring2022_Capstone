// Created by Spring2022_Capstone team


#include "BaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PlayerCamera = CreateAbstractDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	PlayerCamera->SetupAttachment(RootComponent);
	PlayerCamera->bUsePawnControlRotation = true;
	InventoryComponent = CreateAbstractDefaultSubobject<UInventoryComponent>(TEXT("InventoryComponent"));
	LookRate = 5;
	StandingCameraRelativeLocation = FVector(0.0f, 0.0f, 0.0f);
	CrouchingCameraRelativeLocation = FVector(0.0f, 0.0f, 0.0f);
	WalkingSpeed = 600;
	SprintingSpeed = 1000;
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	PlayerCamera->SetRelativeLocation(StandingCameraRelativeLocation);
	GetCharacterMovement()->MaxWalkSpeed = WalkingSpeed;
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABaseCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void ABaseCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X * LookRate);
		AddControllerPitchInput(LookAxisVector.Y * LookRate);

	}
}
void ABaseCharacter::StartCrouch()
{
	Crouch();
	PlayerCamera->SetRelativeLocation(CrouchingCameraRelativeLocation);
}
void ABaseCharacter::StopCrouch()
{
	UnCrouch();
	PlayerCamera->SetRelativeLocation(StandingCameraRelativeLocation);
}
void ABaseCharacter::StartSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = SprintingSpeed;
}
void ABaseCharacter::StopSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = WalkingSpeed;
}