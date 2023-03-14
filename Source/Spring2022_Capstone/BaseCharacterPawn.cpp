// Created by Spring2022_Capstone team


#include "BaseCharacterPawn.h"

// Sets default values
ABaseCharacterPawn::ABaseCharacterPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PlayerCamera = CreateAbstractDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	PlayerCamera->SetupAttachment(RootComponent);
	PlayerCamera->bUsePawnControlRotation = true;
	LookRate = 20;
}
// Called when the game starts or when spawned
void ABaseCharacterPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseCharacterPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//PlayerCamera->SetWorldRotation(GetControlRotation());
}

// Called to bind functionality to input
void ABaseCharacterPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABaseCharacterPawn::Move(const FInputActionValue& Value)
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

void ABaseCharacterPawn::Look(const FInputActionValue& Value)
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

